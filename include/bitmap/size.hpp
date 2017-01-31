//-----------------------------------------------------------------------------
// Copyright (c) 2009-2017 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__size__hpp_INCLUDED_
#define _bitmap__size__hpp_INCLUDED_


namespace bitmap{


	/// \brief A class for manipulating sizes
	/// \tparam ValueType Type of the size data
	template < typename ValueType >
	class size{
	public:
		/// \brief Type of the positions
		using value_type = ValueType;


		/// \brief The width
		value_type& width(){
			return width_;
		}

		/// \brief The height
		value_type& height(){
			return height_;
		}


		/// \brief The width
		value_type const& width()const{
			return width_;
		}

		/// \brief The height
		value_type const& height()const{
			return height_;
		}


		/// \brief Set width and height
		void set(value_type const& width, value_type const& height){
			width_ = width;
			height_ = height;
		}


		/// \brief Constructs a size with width 0 and height 0
		size(): width_(), height_() {}

		/// \brief Constructs a copy
		size(size const&) = default;

		/// \brief Constructs a copy
		size(size&&) = default;

		/// \brief Constructs a size width width and height
		size(value_type const& width, value_type const& height):
			width_(width), height_(height) {}


		/// \brief Copy assignment
		size& operator=(size const&) = default;

		/// \brief Move assignment
		size& operator=(size&&) = default;


		/// \brief Get true, if width and height are positiv
		bool is_positive()const{
			return width() >= value_type() && height() >= value_type();
		}


		/// \brief Get width * height
		value_type const point_count()const{
			return width() * height();
		}

	private:
		value_type width_;
		value_type height_;
	};

	template < typename ValueType >
	bool operator==(size< ValueType > const& a, size< ValueType > const& b){
		return a.width() == b.width() && a.height() == b.height();
	}

	template < typename ValueType >
	bool operator!=(size< ValueType > const& a, size< ValueType > const& b){
		return a != b;
	}


}

#endif
