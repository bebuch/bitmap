//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__exception__hpp_INCLUDED_
#define _bitmap__exception__hpp_INCLUDED_

#include <stdexcept>


namespace bmp{


	/// \brief Exception class for binary_write and binary_read bitmaps
	struct binary_io_error: std::runtime_error{
		using std::runtime_error::runtime_error;
	};


}

#endif
