//-----------------------------------------------------------------------------
// Copyright (c) 2019 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__colormap__hpp_INCLUDED_
#define _bitmap__colormap__hpp_INCLUDED_

#include "pixel.hpp"

#include <vector>
#include <cmath>


namespace bmp::colormap{


	namespace function{


		struct cos_rise{
			double operator()(double value)const noexcept{
				return (std::cos(M_PI + M_PI * value) + 1) / 2;
			}
		};

		struct cos_fall{
			double operator()(double value)const noexcept{
				return (std::cos(M_PI * value) + 1) / 2;
			}
		};

		struct linear_rise{
			double operator()(double value)const noexcept{
				return value;
			}
		};

		struct linear_fall{
			double operator()(double value)const noexcept{
				return 1 - value;
			}
		};


		struct cos{
			cos_rise rise;
			cos_fall fall;
		};

		struct linear{
			linear_rise rise;
			linear_fall fall;
		};


	}


	struct rgb_edges{
		std::vector< double > r;
		std::vector< double > g;
		std::vector< double > b;
	};


	template < typename Functions = function::cos, typename T = unsigned char >
	std::vector< T > make_uniform(
		std::vector< double > const& edges,
		unsigned bits,
		Functions const& fn = function::cos{},
		T const max_value = std::is_floating_point< T >::value
			? 1 : std::numeric_limits< T >::max()
	){
		std::size_t steps = edges.size() - 1;
		double s_diff = 1. / steps;
		std::size_t values = std::pow(2, bits);

		std::vector< T > colormap(values);
		for (std::size_t vi = 0; vi < values; ++vi){
			double v = static_cast< double >(vi) / (values - 1);
			double step_index = (v - std::fmod(v, s_diff)) / s_diff;
			auto step_index_s = static_cast< std::size_t >(
				std::lround(step_index));
			std::size_t si = std::min(step_index_s, steps - 1);

			double s1 = edges[si];
			double s2 = edges[si + 1];

			double from = static_cast< double >(si) / steps;
			double scaled = (v - from) / s_diff;
			scaled = std::max(0., std::min(1., scaled));

			if(s2 > s1){
				colormap[vi] = static_cast< T >(
					(s1 + fn.rise(scaled) * (s2 - s1)) * max_value);
			}else if(s2 < s1){
				colormap[vi] = static_cast< T >(
					(s2 + fn.fall(scaled) * (s1 - s2)) * max_value);
			}else{
				colormap[vi] = static_cast< T >(s1 * max_value);
			}
		}

		return colormap;
	}

	template < typename Functions = function::cos, typename T = unsigned char >
	std::vector< ::bmp::pixel::basic_rgb< T > > make_uniform(
		rgb_edges const& edges,
		unsigned bits,
		Functions const& fn = function::cos{},
		T const max_value = std::is_floating_point< T >::value
			? 1 : std::numeric_limits< T >::max()
	){
		auto r = make_uniform(edges.r, bits, fn, max_value);
		auto g = make_uniform(edges.g, bits, fn, max_value);
		auto b = make_uniform(edges.b, bits, fn, max_value);

		std::vector< ::bmp::pixel::basic_rgb< T > > colormap(r.size());
		for(std::size_t i = 1; i < colormap.size(); ++i){
			colormap[i].r = r[i];
			colormap[i].g = g[i];
			colormap[i].b = b[i];
		}

		return colormap;
	}


}


#endif
