//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__interpolate__hpp_INCLUDED_
#define _bitmap__interpolate__hpp_INCLUDED_

#include "pixel.hpp"


namespace bmp{


	template < typename FT, typename T >
	constexpr T interpolate(FT ratio, T a, T b)noexcept{
		return static_cast< T >(ratio * a + (1 - ratio) * b);
	}

	template < typename FT, typename T >
	constexpr pixel::basic_ga< T > interpolate(
		FT ratio,
		pixel::basic_ga< T > const& a,
		pixel::basic_ga< T > const& b
	)noexcept{
		return {
			interpolate(ratio, a.g, b.g),
			interpolate(ratio, a.a, b.a)
		};
	}

	template < typename FT, typename T >
	constexpr pixel::basic_rgb< T > interpolate(
		FT ratio,
		pixel::basic_rgb< T > const& a,
		pixel::basic_rgb< T > const& b
	)noexcept{
		return {
			interpolate(ratio, a.r, b.r),
			interpolate(ratio, a.g, b.g),
			interpolate(ratio, a.b, b.b)
		};
	}

	template < typename FT, typename T >
	constexpr pixel::basic_rgba< T > interpolate(
		FT ratio,
		pixel::basic_rgba< T > const& a,
		pixel::basic_rgba< T > const& b
	)noexcept{
		return {
			interpolate(ratio, a.r, b.r),
			interpolate(ratio, a.g, b.g),
			interpolate(ratio, a.b, b.b),
			interpolate(ratio, a.a, b.a)
		};
	}


	template < typename FXT, typename FYT, typename T >
	constexpr T interpolate_2d(
		FXT x_ratio, FYT y_ratio, T tl, T tr, T bl, T br
	)noexcept{
		return interpolate(y_ratio,
			interpolate(x_ratio, tl, tr), interpolate(x_ratio, bl, br));
	}


}


#endif