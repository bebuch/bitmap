//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__rect_transform__hpp_INCLUDED_
#define _bitmap__rect_transform__hpp_INCLUDED_

#include "rect.hpp"
#include "matrix3x3.hpp"

#include <array>
#include <cmath>


namespace bmp{


	template < typename T >
	constexpr matrix3x3< T > solve(std::array< point< T >, 4 > const& points){
		auto p1 = points[0];
		auto p2 = points[1];
		auto p3 = points[2];
		auto p4 = points[3];

		T m[3][4] = {
			{p1.x(), p2.x(), p3.x(), p4.x()},
			{p1.y(), p2.y(), p3.y(), p4.y()},
			{1, 1, 1, 1}};

		gaussian_elimination(m);

		return matrix3x3< T >{{
			{m[0][3] * p1.x(), m[1][3] * p2.x(), m[2][3] * p3.x()},
			{m[0][3] * p1.y(), m[1][3] * p2.y(), m[2][3] * p3.y()},
			{m[0][3],          m[1][3],          m[2][3]}}};
	}


	template < typename T >
	constexpr matrix3x3< T > operator*(
		matrix3x3< T > const& m1,
		matrix3x3< T > const& m2
	){
		matrix3x3< T > m{};

		for(std::size_t y = 0; y < 3; ++y){
			for(std::size_t x = 0; x < 3; ++x){
				for(std::size_t i = 0; i < 3; ++i){
					m.d[y][x] += m1.d[y][i] * m2.d[i][x];
				}
			}
		}

		return m;
	}

	template < typename T >
	constexpr point< T > transform(
		matrix3x3< T > const& m,
		point< T > const& p
	){
		T v[3]{p.x(), p.y(), 1};
		T r[3]{};

		for(std::size_t y = 0; y < 3; ++y){
			for(std::size_t x = 0; x < 3; ++x){
				r[y] += m.d[y][x] * v[x];
			}
		}

		return point< T >{r[0] / r[2], r[1] / r[2]};
	}


	template < typename T >
	constexpr matrix3x3< T > rect_transform_homography(
		std::array< point< T >, 4 > const& from,
		std::array< point< T >, 4 > const& to
	){
		return solve(to) * invert(solve(from));
	}

	template < typename T >
	std::array< point< T >, 4 > transform_image_contour(
		matrix3x3< T > const& homography,
		size< std::size_t > const& image_size
	){
		return {
				transform(homography, point< T >{0, 0}),
				transform(homography,
					point< T >{static_cast< T >(image_size.width()), 0}),
				transform(homography,
					point< T >{0, static_cast< T >(image_size.height())}),
				transform(homography, to_point< T >(image_size))
			};
	}

	template < typename T >
	rect< long, long, std::size_t, std::size_t > image_contour(
		std::array< point< T >, 4 > const& c
	){
		using std::min;
		using std::max;
		return {
				point< long >{
					static_cast< long >(std::floor(
						min(min(c[0].x(), c[1].x()), min(c[2].x(), c[3].x())))),
					static_cast< long >(std::floor(
						min(min(c[0].y(), c[1].y()), min(c[2].y(), c[3].y())))),
				},
				point< long >{
					static_cast< long >(std::floor(
						max(max(c[0].x(), c[1].x()), max(c[2].x(), c[3].x())))),
					static_cast< long >(std::floor(
						max(max(c[0].y(), c[1].y()), max(c[2].y(), c[3].y())))),
				}
			};
	}


}


#endif
