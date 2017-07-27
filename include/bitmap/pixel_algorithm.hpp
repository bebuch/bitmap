//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__pixel_algorithm__hpp_INCLUDED_
#define _bitmap__pixel_algorithm__hpp_INCLUDED_

#include "pixel.hpp"

#include <algorithm>


namespace bmp{ namespace pixel{


	template < typename T >
	constexpr basic_ga< T > min(
		basic_ga< T > const& l,
		basic_ga< T > const& r
	)noexcept{
		return {
			::std::min(l.g, r.g),
			::std::min(l.a, r.a)};
	}

	template < typename T >
	constexpr basic_ga< T > max(
		basic_ga< T > const& l,
		basic_ga< T > const& r
	)noexcept{
		return {
			::std::max(l.g, r.g),
			::std::max(l.a, r.a)};
	}

	template < typename T >
	constexpr basic_rgb< T > min(
		basic_rgb< T > const& l,
		basic_rgb< T > const& r
	)noexcept{
		return {
			::std::min(l.r, r.r),
			::std::min(l.g, r.g),
			::std::min(l.b, r.b)};
	}

	template < typename T >
	constexpr basic_rgb< T > max(
		basic_rgb< T > const& l,
		basic_rgb< T > const& r
	)noexcept{
		return {
			::std::max(l.r, r.r),
			::std::max(l.g, r.g),
			::std::max(l.b, r.b)};
	}

	template < typename T >
	constexpr basic_rgba< T > min(
		basic_rgba< T > const& l,
		basic_rgba< T > const& r
	)noexcept{
		return {
			::std::min(l.r, r.r),
			::std::min(l.g, r.g),
			::std::min(l.b, r.b),
			::std::min(l.a, r.a)};
	}

	template < typename T >
	constexpr basic_rgba< T > max(
		basic_rgba< T > const& l,
		basic_rgba< T > const& r
	)noexcept{
		return {
			::std::max(l.r, r.r),
			::std::max(l.g, r.g),
			::std::max(l.b, r.b),
			::std::max(l.a, r.a)};
	}


} }


#endif
