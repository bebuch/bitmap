//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__size_io__hpp_INCLUDED_
#define _bitmap__size_io__hpp_INCLUDED_

#include "size.hpp"

#include <io_tools/expect.hpp>
#include <io_tools/input_wrapper.hpp>


namespace bmp{


	template < typename CharT, typename Traits, typename WT, typename HT >
	std::basic_ostream< CharT, Traits >& operator<<(
		std::basic_ostream< CharT, Traits >& os,
		size< WT, HT > const& data
	){
		return os << data.width() << "x" << data.height();
	}


	template < typename CharT, typename Traits, typename WT, typename HT >
	std::basic_istream< CharT, Traits >& operator>>(
		std::basic_istream< CharT, Traits >& is,
		size< WT, HT >& data
	){
		size< WT, HT > tmp;
		is >> io_tools::input_wrapper(tmp.width());
		if(!io_tools::expect(is, 'x')) return is;
		is >> io_tools::input_wrapper(tmp.height());

		if(is){
			data = std::move(tmp);
		}

		return is;
	}


}


#endif
