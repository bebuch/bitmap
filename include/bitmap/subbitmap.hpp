//-----------------------------------------------------------------------------
// Copyright (c) 2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__subbitmap__hpp_INCLUDED_
#define _bitmap__subbitmap__hpp_INCLUDED_

#include "bitmap.hpp"
#include "pixel.hpp"

#include <type_traits>
#include <cmath>


namespace bitmap::detail{


	template < typename T >
	void copy(
		bitmap< T >& target, bitmap< T > const& ref,
		rect< std::size_t, std::size_t > const& rect,
		point< std::size_t > const& target_start = {}
	){
		for(std::size_t y = 0; y < rect.height(); ++y){
			auto const ref_from = ref.begin()
				+ (rect.y() + y) * ref.width() + rect.x();

			auto const target_from = target.begin()
				+ (target_start.y() + y) * target.width() + target_start.x();

			std::copy(ref_from, ref_from + rect.width(), target_from);
		}
	}


	template < typename FT, typename T >
	constexpr T interpolate(
		FT x_ratio, FT y_ratio, T tl, T tr, T bl, T br
	)noexcept{
		return
			(x_ratio * tl + (1 - x_ratio) * tr) * y_ratio +
			(x_ratio * bl + (1 - x_ratio) * br) * (1 - y_ratio);
	}

	template < typename FT, typename T >
	constexpr T interpolate(
		FT x_ratio, FT y_ratio,
		pixel::basic_ga< T > const& tl, pixel::basic_ga< T > const& tr,
		pixel::basic_ga< T > const& bl, pixel::basic_ga< T > const& br
	)noexcept{
		return pixel::basic_ga< T >{
			interpolate(x_ratio, y_ratio, tl.g, tr.g, bl.g, br.g),
			interpolate(x_ratio, y_ratio, tl.a, tr.a, bl.a, br.a)
		};
	}

	template < typename FT, typename T >
	constexpr T interpolate(
		FT x_ratio, FT y_ratio,
		pixel::basic_rgb< T > const& tl, pixel::basic_rgb< T > const& tr,
		pixel::basic_rgb< T > const& bl, pixel::basic_rgb< T > const& br
	)noexcept{
		return pixel::basic_rgb< T >{
			interpolate(x_ratio, y_ratio, tl.r, tr.r, bl.r, br.r),
			interpolate(x_ratio, y_ratio, tl.g, tr.g, bl.g, br.g),
			interpolate(x_ratio, y_ratio, tl.b, tr.b, bl.b, br.b)
		};
	}

	template < typename FT, typename T >
	constexpr T interpolate(
		FT x_ratio, FT y_ratio,
		pixel::basic_rgba< T > const& tl, pixel::basic_rgba< T > const& tr,
		pixel::basic_rgba< T > const& bl, pixel::basic_rgba< T > const& br
	)noexcept{
		return pixel::basic_rgba< T >{
			interpolate(x_ratio, y_ratio, tl.r, tr.r, bl.r, br.r),
			interpolate(x_ratio, y_ratio, tl.g, tr.g, bl.g, br.g),
			interpolate(x_ratio, y_ratio, tl.b, tr.b, bl.b, br.b),
			interpolate(x_ratio, y_ratio, tl.a, tr.a, bl.a, br.a)
		};
	}

	template < typename FT, typename T >
	void full_interpolate(
		bitmap< T >& target, bitmap< T > const& ref,
		rect< std::size_t, std::size_t > const& rect,
		point< FT > const& ratio,
		point< std::size_t > const& target_start = {}
	){
		for(std::size_t y = 0; y < rect.height(); ++y){
			for(std::size_t x = 0; x < rect.width(); ++x){
				auto const ax = rect.x() + x;
				auto const ay = rect.y() + y;
				target(target_start.x() + x, target_start.y() + y) =
					interpolate(
						ratio.x(), ratio.y(),
						ref(ax, ay), ref(ax + 1, ay),
						ref(ax, ay + 1), ref(ax + 1, ay + 1));
			}
		}
	}

	template < typename XY_T, typename WH_T >
	std::string out_of_range_msg(
		size< std::size_t > const& bmp_size,
		rect< XY_T, WH_T > const& rect
	){
		std::ostringstream os;
		os << "subbitmap: rect(point(x = " << rect.x() << ", y = "
			<< rect.y() << ")[";
		if(std::is_integral_v< XY_T >){
			os << "int";
		}else{
			os << "float -> max(x) = " << std::floor(rect.x())
				<< " + 1, max(y) = " << std::floor(rect.y()) << " + 1";
		}
		os << "], size(width = " << rect.width()
			<< ", height = " << rect.height()
			<< ")) is outside the original bitmap(width = "
			<< bmp_size.width() << ", height = " << bmp_size.height() << ")";
		return os.str();
	}

	template < typename XY_T, typename WH_T >
	std::string neg_size_msg(rect< XY_T, WH_T > const& rect){
		std::ostringstream os;
		os << "subbitmap: rect(point(x = " << rect.x() << ", y = "
			<< rect.y() << "), size(width = " << rect.width()
			<< ", height = " << rect.height() << ")) has negetive size";
		return os.str();
	}


	template < typename XY_T, typename WH_T >
	void subbitmap_check_rect(rect< XY_T, WH_T > const& rect){
		static_assert(std::is_arithmetic_v< XY_T >,
			"rect must have arithmetic x and y");

		static_assert(std::is_integral_v< WH_T >,
			"rect must have integral width and height");

		if(rect.width() < 0 || rect.height() < 0){
			throw std::logic_error(detail::neg_size_msg(rect));
		}
	}


}


namespace bitmap{


	/// \brief Return the pixels in rect as new bitmap, throw if out of range
	template < typename T, typename XY_T, typename WH_T >
	bitmap< T > subbitmap(
		bitmap< T > const& org,
		rect< XY_T, WH_T > const& rect
	){
		detail::subbitmap_check_rect(rect);

		if(rect.x() < 0 || rect.y() < 0){
			throw std::out_of_range(detail::out_of_range_msg(org.size(), rect));
		}

		auto const bitmap_size = size(
				static_cast< std::size_t >(rect.width()),
				static_cast< std::size_t >(rect.height())
			);

		if constexpr(std::is_integral_v< XY_T >){
			auto const int_rect = ::bitmap::rect(point(
					static_cast< std::size_t >(rect.x()),
					static_cast< std::size_t >(rect.y())
				), bitmap_size);

			if(
				int_rect.x() + int_rect.width() > org.width() ||
				int_rect.y() + int_rect.height() > org.height()
			){
				throw std::out_of_range(
					detail::out_of_range_msg(org.size(), rect));
			}

			bitmap< T > result(bitmap_size);
			detail::copy(result, org, int_rect);
			return result;
		}else{
			auto const int_rect = ::bitmap::rect(point(
					static_cast< std::size_t >(std::floor(rect.x())),
					static_cast< std::size_t >(std::floor(rect.y()))
				), bitmap_size);

			if(
				int_rect.x() + 1 + int_rect.width() > org.width() ||
				int_rect.y() + 1 + int_rect.height() > org.height()
			){
				throw std::out_of_range(
					detail::out_of_range_msg(org.size(), rect));
			}

			auto const ratio = point(
				1 - (rect.x() - std::floor(rect.x())),
				1 - (rect.y() - std::floor(rect.y())));
			bitmap< T > result(bitmap_size);
			detail::full_interpolate(result, org, int_rect, ratio);
			return result;
		}
	}

// 	/// \brief Return the pixels in rect as new bitmap, fill if out of range
// 	template < typename T, typename XY_T, typename WH_T >
// 	bitmap< T > subbitmap(
// 		bitmap< T > const& org,
// 		rect< XY_T, WH_T > const& rect,
// 		T const& fill_value
// 	){
// 		template struct detail::rect_check< XY_T, WH_T >;
//
// 		if constexpr(std::is_integral_v< XY_T >){
// // 		auto const xb = rect.x() < 0 ? -rect.x() : 0;
// // 		auto const yb = rect.y() < 0 ? -rect.y() : 0;
// // 		auto const xe = std::min(rect.width(), width() - rect.x());
// // 		auto const ye = std::min(rect.height(), height() - rect.y());
//
//
// 		}else{
//
// 		}
// 	}


}


#endif
