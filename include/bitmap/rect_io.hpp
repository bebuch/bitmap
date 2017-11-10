//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__rect_io__hpp_INCLUDED_
#define _bitmap__rect_io__hpp_INCLUDED_

#include "size_io.hpp"
#include "point_io.hpp"
#include "rect.hpp"


namespace bmp{


	template < typename charT, typename traits,
		typename XT, typename YT, typename WT, typename HT >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		rect< XT, YT, WT, HT > const& data
	){
		return os << data.top_left() << ":" << data.size();
	}


}


#endif
