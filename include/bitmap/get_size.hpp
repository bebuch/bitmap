//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__get_size__hpp_INCLUDED_
#define _bitmap__get_size__hpp_INCLUDED_

#include "bitmap.hpp"

#include <numeric>
#include <functional>


namespace bmp{


	/// \brief Get size of the bitmaps, throw if different sizes
	template < typename Bitmap, typename GetSizeFunction >
	size< std::size_t > get_size(
		std::vector< Bitmap > const& vec,
		GetSizeFunction&& f
	){
		if(vec.empty()) throw std::logic_error("bitmap vector is empty");
		return std::accumulate(
			vec.cbegin() + 1, vec.cend(), f(*vec.cbegin()),
			[&vec, &f](auto& ref, auto& test){
				if(ref == f(test)) return ref;

				std::ostringstream os;
				os << "different image sizes (";
				bool first = true;
				for(auto& img: vec){
					if(first){ first = false; }else{ os << ", "; }
					os << f(img);
				}
				os << ") image";
				throw std::logic_error(os.str());
			});
	}

	template < typename T >
	size< std::size_t > get_size(
		bitmap_vector< T > const& vec
	){
		return get_size(vec,
			[](auto const& bitmap){ return bitmap.size(); });
	}

	template < typename T >
	size< std::size_t > get_size(
		std::vector< std::reference_wrapper< bitmap< T > > > const& vec
	){
		return get_size(vec,
			[](auto const& bitmap){ return bitmap.get().size(); });
	}

	template < typename T >
	size< std::size_t > get_size(
		std::vector< std::reference_wrapper< bitmap< T > const > > const& vec
	){
		return get_size(vec,
			[](auto const& bitmap){ return bitmap.get().size(); });
	}


}

#endif
