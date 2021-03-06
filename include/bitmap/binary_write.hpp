//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__binary_write__hpp_INCLUDED_
#define _bitmap__binary_write__hpp_INCLUDED_

#include "bitmap.hpp"
#include "exception.hpp"

#include "detail/binary_io_flags.hpp"
#include "detail/valid_binary_format.hpp"

#include <boost/endian/arithmetic.hpp>

#include <string>
#include <fstream>
#include <cstdint>


namespace bmp{


	/// \brief Write bitmap to std::ostream
	///
	/// \throw binary_io_error
	template < typename T >
	void binary_write(
		bitmap< T > const& bitmap,
		std::ostream& os,
		boost::endian::order endianness = boost::endian::order::native
	){
		static_assert(detail::is_valid_binary_format_v< T >,
			"Your value_type is not supported by bmp::binary_write");

		using namespace boost::endian;
		using pixel::channel_count_v;
		using value_type = pixel::channel_type_t< T >;

		static_assert(sizeof(value_type) <= 256);
		static_assert(sizeof(T) == sizeof(value_type) * channel_count_v< T >);
		if constexpr(std::is_floating_point_v< value_type >){
			if(endianness != boost::endian::order::native){
				throw std::runtime_error("endian conversion is "
					"not supported for floating point types");
			}
		}

		// header informations
		big_uint32_t const magic = detail::io_magic;

		big_uint8_t const version = 0x00;
		big_uint8_t const size_in_byte = sizeof(value_type);
		big_uint8_t const channel_count = channel_count_v< T >;
		auto const endian_flag = [endianness]{
			switch(endianness){
				case boost::endian::order::little:
					return detail::binary_endian_flags::is_little_endian;
				case boost::endian::order::big:
					return detail::binary_endian_flags::is_big_endian;
				default:
					throw std::logic_error(
						"unknown boost::endian::order: "
						+ std::to_string(std::uint32_t(endianness)));
			}
		}();
		big_uint8_t const flags = [endian_flag]()->std::uint8_t{
				return (detail::binary_io_flags_v< value_type > & 0x0F) |
					std::uint8_t(endian_flag);
			}();

		big_uint64_t const width  = bitmap.width();
		big_uint64_t const height = bitmap.height();

		// write the file header
		os.write(reinterpret_cast< char const* >(&magic),         4);
		os.write(reinterpret_cast< char const* >(&version),       1);
		os.write(reinterpret_cast< char const* >(&size_in_byte),  1);
		os.write(reinterpret_cast< char const* >(&channel_count), 1);
		os.write(reinterpret_cast< char const* >(&flags),         1);
		os.write(reinterpret_cast< char const* >(&width),         8);
		os.write(reinterpret_cast< char const* >(&height),        8);

		if(!os.good()){
			throw binary_io_error("can't write binary bitmap format header");
		}

		if constexpr(std::is_same_v< T, bool >){
			big_uint8_t data = 0;
			std::size_t i = 0;
			for(bool v: bitmap){
				data <<= 1;
				data |= v ? 1 : 0;
				if(++i % 8 == 0){
					os.write(reinterpret_cast< char const* >(&data), 1);
					data = 0;
				}
			}
			if(i % 8 != 0){
				data <<= (8 - (i % 8));
				os.write(reinterpret_cast< char const* >(&data), 1);
			}
		}else if(endianness == boost::endian::order::native){
			os.write(
				reinterpret_cast< char const* >(bitmap.data()),
				width * height * sizeof(T));
		}else if constexpr(!std::is_floating_point_v< value_type >){
			for(auto v: bitmap){
				for(std::size_t i = 0; i < channel_count_v< T >; ++i){
					auto& c = *(reinterpret_cast< value_type* >(&v) + i);
					c = endian_reverse(c);
				}
				os.write(reinterpret_cast< char const* >(&v), sizeof(T));
			}
		}

		if(!os.good()){
			throw binary_io_error("can't write binary bitmap format data");
		}
	}


	/// \brief Write bitmap to disk by a given filename
	///
	/// \throw binary_io_error
	template < typename T >
	void binary_write(
		bitmap< T > const& bitmap,
		std::string const& filename,
		boost::endian::order endianness = boost::endian::order::native
	){
		std::ofstream os(filename.c_str(), std::ios_base::binary);

		if(!os.is_open()){
			throw binary_io_error("can't open file: " + filename);
		}

		try{
			binary_write(bitmap, os, endianness);
		}catch(binary_io_error const& e){
			throw binary_io_error(std::string(e.what()) + ": " + filename);
		}
	}


}

#endif
