//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__binary_read__hpp_INCLUDED_
#define _bitmap__binary_read__hpp_INCLUDED_

#include "bitmap.hpp"
#include "exception.hpp"

#include "detail/binary_io_flags.hpp"
#include "detail/valid_binary_format.hpp"

#include <boost/endian/arithmetic.hpp>

#include <string>
#include <fstream>
#include <cstdint>


namespace bitmap{


	struct binary_header{
		uint8_t version;
		uint8_t size_in_byte;
		uint8_t channel_count;
		uint8_t flags;

		size_t width;
		size_t height;
	};

	/// \brief Read binary bitmap format header from std::ostream
	///
	/// \throw binary_io_error
	void binary_read_header(std::ostream& os){
		static_assert(detail::is_valid_binary_format_v< T >,
			"Your value_type is not supported by bitmap::binary_write");

		using namespace boost::endian;
		using pixel::channel_count_v;
		using value_type = pixel::channel_type_t< T >;

		static_assert(sizeof(value_type) <= 256);
		static_assert(sizeof(T) == sizeof(value_type) * channel_count_v< T >);

		// read the file header
		big_uint32_t magic;
		os.read(reinterpret_cast< char const* >(&magic), 4);
		if(magic != detail::io_magic){
			throw binary_io_error("wrong magic number");
		}

		big_uint8_t version;
		os.read(reinterpret_cast< char const* >(&version), 1);
		if(version != 0x00){
			throw binary_io_error("only version 0 is supported"); // TODO: more info
		}

		big_uint8_t size_in_byte;
		big_uint8_t channel_count;
		big_uint8_t flags;
		big_uint64_t width;
		big_uint64_t height;

		os.read(reinterpret_cast< char const* >(&size_in_byte),  1);
		os.read(reinterpret_cast< char const* >(&channel_count), 1);
		os.read(reinterpret_cast< char const* >(&flags),         1);
		os.read(reinterpret_cast< char const* >(&width),         8);
		os.read(reinterpret_cast< char const* >(&height),        8);

		if(!os.good()){
			throw binary_io_error("can't read binary bitmap format header");
		}

		return binary_header{
			version, size_in_byte, channel_count, flags, width, height
		};
	}

	/// \brief Read bitmap from std::ostream
	///
	/// \throw binary_io_error
	template < typename T >
	void binary_read(
		bitmap< T >& bitmap,
		std::ostream& os,
		bool ignore_signed = true
	){
		auto const header = binary_read_header(os);

		uint8_t const ref_flags = detail::binary_io_flags_v< value_type >;
		auto const ref_type_flag = binary_type_flags(ref_flags & 0x0F);
		auto const ref_endian_flag = binary_endian_flags(ref_flags & 0xF0);

		auto const test_type_flag = binary_type_flags(header.flags & 0x0F);
		auto const test_endian_flag = binary_endian_flags(header.flags & 0xF0);

		if(ignore_signed){
			if(ref_type_flag == binary_type_flags::is_signed){
				ref_type_flag = binary_type_flags::is_unsigned;
			}
			if(test_type_flag == binary_type_flags::is_signed){
				test_type_flag = binary_type_flags::is_unsigned;
			}
		}

		if(test_type_flag != ref_type_flag){
			auto const print_type_flag =
				[ignore_signed](binary_type_flags flag){
					switch(flag){
						case binary_type_flags::is_unsigned:
							if(ignore_signed) return "integer";
							return "unsigned integer";
						case binary_type_flags::is_signed:
							if(ignore_signed) return "integer";
							return "signed integer";
						case binary_type_flags::is_floating_point:
							return "floating point";
						case binary_type_flags::is_bool:
							return "bool";
						default:
							throw std::logic_error(
								"unknown binary_type_flags flag: "
								+ std::to_string(std::uint8_t(flag)));
					}
				};

			std::ostringstream os;
			os << "wrong type " << print_type_flag(test_type_flag)
				<< ", expected " << print_type_flag(ref_type_flag);
			throw binary_io_error(os.str());
		}

		if(header.size_in_byte != sizeof(value_type)){
			throw binary_io_error("wrong value_type size "
				+ std::to_string(header.size_in_byte) + ", expected "
				+ std::to_string(sizeof(value_type)));
		}

		if(header.channel_count != channel_count_v< T >){
			throw binary_io_error("wrong channel count "
				+ std::to_string(header.channel_count) + ", expected "
				+ std::to_string(channel_count_v< T >));
		}

		if(
			test_endian_flag != binary_endian_flags::is_big_endian &&
			test_endian_flag != binary_endian_flags::is_little_endian
		){
			throw std::logic_error("unknown binary_endian_flags flag: "
				+ std::to_string(std::uint8_t(test_endian_flag)));
		}


		if constexpr(std::is_same_v< T, bool >){
			big_uint64_t data = 0;
			std::size_t i = 0;
			for(bool v: bitmap){
				data <<= 1;
				data |= v ? 1 : 0;
				if(++i % 64 == 0){
					os.write(reinterpret_cast< char const* >(&data), 8);
					data = 0;
				}
			}
			if(i % 64 != 0){
				os.write(reinterpret_cast< char const* >(&data), 8);
			}
		}else{
			os.read(
				reinterpret_cast< char const* >(bitmap.data()),
				width * height * sizeof(T));
		}

		if(!os.good()){
			throw binary_io_error("can't read binary bitmap format data");
		}
	}

	/// \brief Read bitmap from disk by a given filename
	///
	/// \throw binary_io_error
	template < typename T >
	void binary_read(
		bitmap< T >& bitmap,
		std::string const& filename,
		bool ignore_signed = true
	){
		std::ifstream is(
			filename.c_str(),
			std::ios_base::in | std::ios_base::binary
		);

		if(!is.is_open()){
			throw binary_io_error("can't open file: " + filename);
		}

		try{
			binary_read(bitmap, is, ignore_signed);
		}catch(binary_io_error const& error){
			throw binary_io_error(std::string(error.what()) + ": " + filename);
		}
	}


}

#endif
