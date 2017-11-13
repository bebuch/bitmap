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


namespace bmp{


	template < typename charT, typename traits, typename XT, typename YT >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		point< XT, YT > const& data
	){
		return os << data.x() << "x" << data.y();
	}


	template < typename charT, typename traits, typename XT, typename YT >
	std::basic_istream< charT, traits >& operator>>(
		std::basic_istream< charT, traits >& is,
		point< XT, YT >& data
	){
		point< XT, YT > tmp;
		is >> tmp.x();
		if(!io_tools::expect(is, 'x')) return is;
		is >> tmp.y();

		if(is){
			data = std::move(tmp);
		}

		return is;
	}


}


#endif
