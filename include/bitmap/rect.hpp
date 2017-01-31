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

#include <algorithm>

#include "point.hpp"
#include "size.hpp"

namespace bitmap{


	/// \brief A class for manipulating rectangles
	/// \tparam ValueType Type of the position data
	template < typename PositionType, typename SizeType = PositionType >
	class rect{
	public:
		/// \brief Type of the rect position
		using position_type = PositionType;

		/// \brief Type of the rect size
		using size_type = SizeType;


		/// \brief Constructs a blank rect
		rect() = default;

		/// \brief Copy constructor
		rect(rect const&) = default;

		/// \brief Move constuctor
		rect(rect&&) = default;

		/// \brief Constructs a rect on position (0, 0), with size width and height
		rect(size_type const& width, size_type const& height):
			size_(width, height)
			{}

		/// \brief Constructs a rect on position (0, 0), with size size.width and size.height
		rect(bitmap::size< size_type > const& size):
			size_(size)
			{}

		/// \brief Constructs a rect on position (x, y), with size width and height
		rect(position_type const& x, position_type const& y, size_type const& width, size_type const& height):
			top_left_(x, y),
			size_(width, height)
			{}

		/// \brief Constructs a rect on position (0, 0), with size bottom_right.x + 1 as width and bottom_right.y + 1 as height
		rect(point< position_type > const& bottom_right):
			size_(bottom_right.x() + 1, bottom_right.y() + 1)
			{}

		/// \brief Constructs a rect on position (top_left.x, top_left.y), with size bottom_right.x - top_left.x + 1 as width and bottom_right.y - top_left.x + 1 as height
		rect(point< position_type > const& top_left, point< position_type > const& bottom_right):
			top_left_(top_left),
			size_(bottom_right.x() - top_left.x() + 1, bottom_right.y() - top_left.y() + 1)
			{}

		/// \brief Constructs a rect on position (top_left.x, top_left.y), with size size.width and size.height
		rect(point< position_type > const& top_left, size< size_type > const& size):
			top_left_(top_left),
			size_(size)
			{}


		/// \brief Get true, if width or height is zero
		bool is_empty()const{
			return width() == size_type() && height() == size_type();
		}

		/// \brief Get true, if width and height are positv
		bool is_positive()const{
			return size_.is_positive();
		}


		/// \brief Copy assignment
		rect& operator=(rect const&) = default;

		/// \brief Move assignment
		rect& operator=(rect&&) = default;


		/// \brief Get the x position
		position_type const x()const{
			return top_left_.x();
		}

		/// \brief Get the y position
		position_type const y()const{
			return top_left_.y();
		}

		/// \brief Get the width
		size_type const width()const{
			return size_.width();
		}

		/// \brief Get the height
		size_type const height()const{
			return size_.height();
		}

		/// \brief Get the size
		bitmap::size< size_type > const size()const{
			return size_;
		}

		/// \brief Get width() * height()
		size_type const number_of_points()const{
			return width() * height();
		}


		/// \brief Get the top point
		position_type const top()const{
			return y();
		}

		/// \brief Get the bottom point
		position_type const bottom()const{
			return size_.height() + top_left_.y() - 1;
		}

		/// \brief Get the left point
		position_type const left()const{
			return x();
		}

		/// \brief Get the right point
		position_type const right()const{
			return size_.width() + top_left_.x() - 1;
		}


		/// \brief Get the top left corner
		point< position_type > const top_left()const{
			return top_left_;
		}

		/// \brief Get the top right corner
		point< position_type > const top_right()const{
			return point< PositionType >(top(), right());
		}

		/// \brief Get the bottom left corner
		point< position_type > const bottom_left()const{
			return point< PositionType >(bottom(), left());
		}

		/// \brief Get the bottom right corner
		point< position_type > const bottom_right()const{
			return point< PositionType >(bottom(), right());
		}


		/// \brief Set the x position
		void set_x(position_type const& x){
			top_left_.x() = x;
		}

		/// \brief Set the y position
		void set_y(position_type const& y){
			top_left_.y() = y;
		}

		/// \brief Set the width
		void set_width(size_type const& width){
			size_.width() = width;
		}

		/// \brief Set the height
		void set_height(size_type const& height){
			size_.height() = height;
		}

		/// \brief Set width and height
		void set_size(bitmap::size< size_type > const& size){
			size_ = size;
		}

		/// \brief Set width and height
		void set_size(size_type const& width, size_type const& height){
			set_size(bitmap::size< size_type >{width, height});
		}


		/// \brief Set the top point
		void set_top(position_type const& top){
			top_left_.x() = top;
		}

		/// \brief Set the bottom point
		void set_bottom(position_type const& bottom){
			size_.height() = bottom - top_left_.y() + 1;
		}

		/// \brief Set the left point
		void set_left(position_type const& left){
			top_left_.y() = left;
		}

		/// \brief Set the right point
		void set_right(position_type const& right){
			size_.width() = right - top_left_.x() + 1;
		}


		/// \brief Set the top left corner
		void set_top_left(point< position_type > const& topLeft){
			top_left_ = topLeft;
		}

		/// \brief Set the top right corner
		void set_top_right(point< position_type > const& topRight){
			set_top(topRight.x);
			set_right(topRight.y);
		}

		/// \brief Set the bottom left corner
		void set_bottom_left(point< position_type > const& bottomLeft){
			set_left(bottomLeft.x);
			set_bottom(bottomLeft.y);
		}

		/// \brief Set the bottom right corner
		void set_bottom_right(point< position_type > const& bottomRight){
			set_right(bottomRight.x);
			set_bottom(bottomRight.y);
		}


		/// \brief Moves the rect in horizontal direction
		void move(point< position_type > const& translation){
			move_horizontally(translation.x);
			move_vertically(translation.y);
		}

		/// \brief Moves the rect in horizontal direction
		void move_horizontally(position_type const& translation){
			top_left_.x() += translation;
		}

		/// \brief Moves the rect in vertical direction
		void move_vertically(position_type const& translation){
			top_left_.y() += translation;
		}

	private:
		/// \brief The point in the top left corner
		bitmap::point< position_type > top_left_;

		/// \brief The point in the bottom right corner
		bitmap::size< size_type > size_;
	};



	/// \brief true, if the rectangles are identical; false otherwise
	template < typename PositionType, typename SizeType >
	inline
	bool
	operator==(
		rect< PositionType, SizeType > const& lhs,
		rect< PositionType, SizeType > const& rhs
	){
		return lhs.top_left() == rhs.top_left() && lhs.size() == rhs.size();
	}

	/// \brief false, if the rectangles are identical; true otherwise
	template < typename PositionType, typename SizeType >
	inline
	bool
	operator!=(
		rect< PositionType, SizeType > const& lhs,
		rect< PositionType, SizeType > const& rhs
	){
		return !(lhs == rhs);
	}


	/// \brief Get a rect that contains both rects
	template < typename PositionType, typename SizeType >
	inline
	rect< PositionType, SizeType >
	join(
		rect< PositionType, SizeType > const& lhs,
		rect< PositionType, SizeType > const& rhs
	){
		return rect< PositionType, SizeType >(
			bitmap::point< PositionType >(
				std::min(lhs.left(), rhs.left()),
				std::min(lhs.top(), rhs.top())
			),
			bitmap::point< PositionType >(
				std::max(lhs.right(), rhs.right()),
				std::max(lhs.bottom(), rhs.bottom())
			)
		);
	}


	/// \brief Get true, if point is in rect
	template < typename PositionType, typename SizeType, typename DataType >
	inline
	bool
	contains(
		rect< PositionType, SizeType > const& rect,
		point< DataType > const& point
	){
		return
			point.x() >= rect.left()  &&
			point.y() >= rect.top()   &&
			point.x() <  rect.right() &&
			point.y() <  rect.bottom();
	}

	/// \brief Get true, if test is in reference
	template < typename PositionType, typename SizeType >
	inline
	bool
	contains(
		rect< PositionType, SizeType > const& reference,
		rect< PositionType, SizeType > const& test
	){
		return
			test.left()   >= reference.left()  &&
			test.top()    >= reference.top()   &&
			test.right()  <= reference.right() &&
			test.bottom() <= reference.bottom();
	}


}

#endif
