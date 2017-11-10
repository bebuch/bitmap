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

#include "point.hpp"
#include "matrix3x3.hpp"

#include <array>


namespace bmp{


	template < typename T, std::size_t Y, std::size_t X >
	void swap_lines(T(&m)[Y][X], std::size_t y1, std::size_t y2){
		for(std::size_t i = 0; i < X; ++i){
			using std::swap;
			swap(m[y1][i], m[y2][i]);
		}
	}

	template < typename T >
	constexpr matrix3x3< T > invert(matrix3x3< T > const& d){
		T m[3][6] = {
			{d.d[0][0], d.d[0][1], d.d[0][2], 1, 0, 0},
			{d.d[1][0], d.d[1][1], d.d[1][2], 0, 1, 0},
			{d.d[2][0], d.d[2][1], d.d[2][2], 0, 0, 1}};

		for(std::size_t i = 0; i < 3; ++i){
			if(m[i][i] == 0){
				std::size_t y = i + 1;
				for(; y < 3; ++y){
					if(m[y][i] != 0){
						swap_lines(m, i, y);
						break;
					}
				}
				if(y == 3){
					throw std::logic_error("can't invert matrix");
				}
			}

			for(std::size_t x = i + 1; x < 6; ++x){
				m[i][x] /= m[i][i];
			}
			m[i][i] = 1;

			for(std::size_t y = i + 1; y < 3; ++y){
				for(std::size_t x = i + 1; x < 6; ++x){
					m[y][x] -= m[y][i] * m[i][x];
				}
				m[y][i] = 0;
			}
		}

		for(std::size_t i = 2; i > 0; --i){
			for(std::size_t y = 0; y < i; ++y){
				for(std::size_t x = 3; x < 6; ++x){
					m[y][x] -= m[y][i] * m[i][x];
				}
			}
		}

		return matrix3x3< T >{{
			{m[0][3], m[0][4], m[0][5]},
			{m[1][3], m[1][4], m[1][5]},
			{m[2][3], m[2][4], m[2][5]}}};
	}

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


		for(std::size_t i = 0; i < 3; ++i){
			if(m[i][i] == 0){
				std::size_t y = i + 1;
				for(; y < 3; ++y){
					if(m[y][i] != 0){
						swap_lines(m, i, y);
						break;
					}
				}
				if(y == 3){
					throw std::logic_error("can't solve equation");
				}
			}

			for(std::size_t x = i + 1; x < 4; ++x){
				m[i][x] /= m[i][i];
			}
			m[i][i] = 1;

			for(std::size_t y = i + 1; y < 3; ++y){
				for(std::size_t x = i + 1; x < 4; ++x){
					m[y][x] -= m[y][i] * m[i][x];
				}
				m[y][i] = 0;
			}
		}

		for(std::size_t i = 2; i > 0; --i){
			for(std::size_t y = 0; y < i; ++y){
				m[y][3] -= m[y][i] * m[i][3];
			}
		}

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
	constexpr point< T > convert(
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


}


#endif
