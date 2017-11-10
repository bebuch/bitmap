//-----------------------------------------------------------------------------
// Copyright (c) 2009-2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__matrix3x3_io__hpp_INCLUDED_
#define _bitmap__matrix3x3_io__hpp_INCLUDED_

#include "matrix3x3.hpp"

#include <io_tools/c_array.hpp>

#include <ostream>


namespace bmp{


	template < typename charT, typename traits, typename T >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		matrix3x3< T > const& m
	){
		using ::io_tools::c_array::operator<<;
		return os << m.d;
	}


}


#endif
