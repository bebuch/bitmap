//-----------------------------------------------------------------------------
// Copyright (c) 2009-2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__rect__hpp_INCLUDED_
#define _bitmap__rect__hpp_INCLUDED_

#include "point.hpp"
#include "size.hpp"

#include <algorithm>


namespace bmp{


	/// \brief A class for manipulating rectangles
	template <
		typename XT,
		typename YT = XT,
		typename WT = XT,
		typename HT = YT >
	class rect{
	public:
		/// \brief Type of the x position
		using x_type = XT;

		/// \brief Type of the y position
		using y_type = YT;

		/// \brief Type of the width
		using width_type = WT;

		/// \brief Type of the height
		using height_type = HT;

		/// \brief Type of the rect position
		using pos_type = ::bmp::point< x_type, y_type >;

		/// \brief Type of the rect size
		using size_type = ::bmp::size< width_type, height_type >;


		/// \brief Constructs a blank rect
		constexpr rect() = default;

		/// \brief Copy constructor
		constexpr rect(rect const&) = default;

		/// \brief Move constuctor
		constexpr rect(rect&&) = default;

		/// \brief Constructs a rect on position (0, 0), with size width and
		///        height
		constexpr rect(width_type const& width, height_type const& height):
			size_(width, height)
			{}

		/// \brief Constructs a rect on position (0, 0), with size size.width
		///        and size.height
		constexpr rect(size_type const& size):
			size_(size)
			{}

		/// \brief Constructs a rect on position (x, y), with size width and
		///        height
		constexpr rect(
			x_type const& x,
			y_type const& y,
			width_type const& width,
			height_type const& height
		):
			top_left_(x, y),
			size_(width, height)
			{}

		/// \brief Constructs a rect on position (0, 0), with size
		///        bottom_right.x + 1 as width and bottom_right.y + 1 as height
		constexpr rect(pos_type const& bottom_right):
			size_(bottom_right.x() + 1, bottom_right.y() + 1)
			{}

		/// \brief Constructs a rect on position (top_left.x, top_left.y), with
		///        size bottom_right.x - top_left.x + 1 as width and
		///        bottom_right.y - top_left.x + 1 as height
		constexpr rect(pos_type const& top_left, pos_type const& bottom_right):
			top_left_(top_left),
			size_(
				static_cast< width_type >(bottom_right.x() - top_left.x() + 1),
				static_cast< height_type >(bottom_right.y() - top_left.y() + 1))
			{}

		/// \brief Constructs a rect on position (top_left.x, top_left.y), with
		///        size size.width and size.height
		constexpr rect(pos_type const& top_left, size_type const& size):
			top_left_(top_left),
			size_(size)
			{}


		/// \brief Copy assignment
		constexpr rect& operator=(rect const&) = default;

		/// \brief Move assignment
		constexpr rect& operator=(rect&&) = default;


		/// \brief Get true, if width or height is zero
		constexpr bool is_empty()const{
			return width() == width_type() && height() == height_type();
		}

		/// \brief Get true, if width and height are positv
		constexpr bool is_positive()const{
			return size_.is_positive();
		}


		/// \brief Get the x position
		constexpr x_type const x()const{
			return top_left_.x();
		}

		/// \brief Get the y position
		constexpr y_type const y()const{
			return top_left_.y();
		}

		/// \brief Get the width
		constexpr width_type const width()const{
			return size_.width();
		}

		/// \brief Get the height
		constexpr height_type const height()const{
			return size_.height();
		}

		/// \brief Get the size
		constexpr size_type const size()const{
			return size_;
		}

		/// \brief Get width() * height()
		constexpr auto area()const{
			return size_.area();
		}


		/// \brief Get the top point
		constexpr y_type const top()const{
			return y();
		}

		/// \brief Get the bottom point
		constexpr y_type const bottom()const{
			return size_.height() + top_left_.y() - 1;
		}

		/// \brief Get the left point
		constexpr x_type const left()const{
			return x();
		}

		/// \brief Get the right point
		constexpr x_type const right()const{
			return size_.width() + top_left_.x() - 1;
		}


		/// \brief Get the top left corner
		constexpr pos_type const top_left()const{
			return top_left_;
		}

		/// \brief Get the top right corner
		constexpr pos_type const top_right()const{
			return {top(), right()};
		}

		/// \brief Get the bottom left corner
		constexpr pos_type const bottom_left()const{
			return {bottom(), left()};
		}

		/// \brief Get the bottom right corner
		constexpr pos_type const bottom_right()const{
			return {bottom(), right()};
		}


		/// \brief Set the x position
		constexpr void set_x(x_type const& x){
			top_left_.x() = x;
		}

		/// \brief Set the y position
		constexpr void set_y(y_type const& y){
			top_left_.y() = y;
		}

		/// \brief Set the width
		constexpr void set_width(width_type const& width){
			size_.width() = width;
		}

		/// \brief Set the height
		constexpr void set_height(height_type const& height){
			size_.height() = height;
		}

		/// \brief Set width and height
		constexpr void set_size(size_type const& size){
			size_ = size;
		}

		/// \brief Set width and height
		constexpr void set_size(
			width_type const& width,
			height_type const& height
		){
			set_size(size_type{width, height});
		}


		/// \brief Set the top point
		constexpr void set_top(y_type const& top){
			top_left_.x() = top;
		}

		/// \brief Set the bottom point
		constexpr void set_bottom(y_type const& bottom){
			size_.height() = bottom - top_left_.y() + 1;
		}

		/// \brief Set the left point
		constexpr void set_left(x_type const& left){
			top_left_.y() = left;
		}

		/// \brief Set the right point
		constexpr void set_right(x_type const& right){
			size_.width() = right - top_left_.x() + 1;
		}


		/// \brief Set the top left corner
		constexpr void set_top_left(pos_type const& top_left){
			top_left_ = top_left;
		}

		/// \brief Set the top right corner
		constexpr void set_top_right(pos_type const& top_right){
			set_top(top_right.x);
			set_right(top_right.y);
		}

		/// \brief Set the bottom left corner
		constexpr void set_bottom_left(pos_type const& bottom_left){
			set_left(bottom_left.x);
			set_bottom(bottom_left.y);
		}

		/// \brief Set the bottom right corner
		constexpr void set_bottom_right(pos_type const& bottom_right){
			set_right(bottom_right.x);
			set_bottom(bottom_right.y);
		}


		/// \brief Moves the rect in horizontal direction
		constexpr void move(pos_type const& translation){
			move_horizontally(translation.x);
			move_vertically(translation.y);
		}

		/// \brief Moves the rect in horizontal direction
		constexpr void move_horizontally(x_type const& translation){
			top_left_.x() += translation;
		}

		/// \brief Moves the rect in vertical direction
		constexpr void move_vertically(y_type const& translation){
			top_left_.y() += translation;
		}

	private:
		/// \brief The point in the top left corner
		pos_type top_left_;

		/// \brief The point in the bottom right corner
		size_type size_;
	};



	/// \brief true, if the rectangles are identical; false otherwise
	template < typename XT, typename YT, typename WT, typename HT >
	constexpr bool operator==(
		rect< XT, YT, WT, HT > const& l,
		rect< XT, YT, WT, HT > const& r
	){
		return l.top_left() == r.top_left() && l.size() == r.size();
	}

	/// \brief false, if the rectangles are identical; true otherwise
	template < typename XT, typename YT, typename WT, typename HT >
	constexpr bool operator!=(
		rect< XT, YT, WT, HT > const& l,
		rect< XT, YT, WT, HT > const& r
	){
		return !(l == r);
	}


	/// \brief Get a rect that contains both rects
	template < typename XT, typename YT, typename WT, typename HT >
	constexpr auto join(
		rect< XT, YT, WT, HT > const& l,
		rect< XT, YT, WT, HT > const& r
	){
		return rect< XT, YT, WT, HT >(
			point< XT, YT >(
				std::min(l.left(), r.left()),
				std::min(l.top(), r.top())
			),
			point< XT, YT >(
				std::max(l.right(), r.right()),
				std::max(l.bottom(), r.bottom())
			)
		);
	}


	/// \brief Get true, if point is in rect
	template < typename XT, typename YT, typename WT, typename HT,
		typename PXT, typename PYT >
	constexpr bool contains(
		rect< XT, YT, WT, HT > const& rect,
		point< PXT, PYT > const& point
	){
		return
			point.x() >= rect.left()  &&
			point.y() >= rect.top()   &&
			point.x() <  rect.right() &&
			point.y() <  rect.bottom();
	}

	/// \brief Get true, if test is in reference
	template < typename XT, typename YT, typename WT, typename HT >
	constexpr bool contains(
		rect< XT, YT, WT, HT > const& reference,
		rect< XT, YT, WT, HT > const& test
	){
		return
			test.left()   >= reference.left()  &&
			test.top()    >= reference.top()   &&
			test.right()  <= reference.right() &&
			test.bottom() <= reference.bottom();
	}


}

#endif
