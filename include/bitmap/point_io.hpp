//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
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
#include <io_tools/input_wrapper.hpp>


namespace bmp{


	template < typename CharT, typename Traits, typename XT, typename YT >
	std::basic_ostream< CharT, Traits >& operator<<(
		std::basic_ostream< CharT, Traits >& os,
		point< XT, YT > const& data
	){
		return os << data.x() << "x" << data.y();
	}


	template < typename CharT, typename Traits, typename XT, typename YT >
	std::basic_istream< CharT, Traits >& operator>>(
		std::basic_istream< CharT, Traits >& is,
		point< XT, YT >& data
	){
		point< XT, YT > tmp;
		is >> io_tools::input_wrapper(tmp.x());
		if(!io_tools::expect(is, 'x')) return is;
		is >> io_tools::input_wrapper(tmp.y());

		if(is){
			data = std::move(tmp);
		}

		return is;
	}


}


#endif
