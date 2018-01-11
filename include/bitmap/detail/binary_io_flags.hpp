//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__detail__binary_io_flags__hpp_INCLUDED_
#define _bitmap__detail__binary_io_flags__hpp_INCLUDED_

#include <cstdint>
#include <type_traits>

#include <boost/endian/conversion.hpp>


namespace bmp::detail{


	constexpr std::uint32_t io_magic = 0x62626621;

	enum class binary_type_flags: std::uint8_t{
		is_unsigned       = 0x00,
		is_signed         = 0x01,
		is_floating_point = 0x02,
		is_bool           = 0x03
	};

	enum class binary_endian_flags: std::uint8_t{
		is_big_endian     = 0x00,
		is_little_endian  = 0x10
	};

	template < typename T >
	constexpr std::uint8_t binary_io_flags_v = static_cast< std::uint8_t >(
		std::is_same_v< T, bool > ? binary_type_flags::is_bool :
		std::is_floating_point_v< T > ? binary_type_flags::is_floating_point :
		std::is_signed_v< T > ? binary_type_flags::is_signed :
			binary_type_flags::is_unsigned) |
		static_cast< std::uint8_t >(
			boost::endian::order::native == boost::endian::order::little
				? binary_endian_flags::is_little_endian
				: binary_endian_flags::is_big_endian);


}


#endif
