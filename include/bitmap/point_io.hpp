//-----------------------------------------------------------------------------
// Copyright (c) 2009-2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__point_io__hpp_INCLUDED_
#define _bitmap__point_io__hpp_INCLUDED_

#include "point.hpp"

#include <io_tools/expect.hpp>


namespace bitmap{


	template < typename charT, typename traits, typename T >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		point< T > const& data
	){
		return os << data.x() << "x" << data.y();
	}


	template < typename charT, typename traits, typename T >
	std::basic_istream< charT, traits >& operator>>(
		std::basic_istream< charT, traits >& is,
		point< T >& data
	){
		point< T > tmp;
		is >> tmp.x();
		if(!io_tools::expect(is, 'x')) return is;
		is >> tmp.y();

		data = std::move(tmp);

		return is;
	}


}


#endif
