//-----------------------------------------------------------------------------
// Copyright (c) 2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__pixel_output__hpp_INCLUDED_
#define _bitmap__pixel_output__hpp_INCLUDED_

#include "pixel.hpp"

#include <ostream>


namespace bmp{ namespace pixel{


	template < typename T >
	std::ostream& operator<<(std::ostream& os, basic_ga< T > const& v){
		return os << '{' << v.g << ", " << v.a << '}';
	}

	template < typename T >
	std::ostream& operator<<(std::ostream& os, basic_rgb< T > const& v){
		return os << '{' << v.r << ", " << v.g << ", " << v.b << '}';
	}

	template < typename T >
	std::ostream& operator<<(std::ostream& os, basic_rgba< T > const& v){
		return os << '{' << v.r << ", " << v.g << ", " << v.b << ", "
			<< v.a << '}';
	}


} }


#endif
