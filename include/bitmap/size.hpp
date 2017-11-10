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


namespace bmp{


	namespace detail{


		template < typename WT, typename HT >
		struct size_base{};

		template < typename T >
		struct size_base< T, T >{
			/// \brief Type of width and height
			using value_type = T;
		};


	}


	/// \brief A class for manipulating sizes
	template < typename WT, typename HT = WT >
	class size: public detail::size_base< WT, HT >{
	public:
		/// \brief Type of the width
		using w_type = WT;

		/// \brief Type of the height
		using h_type = HT;


		/// \brief Constructs a size with width 0 and height 0
		constexpr size(): width_(), height_() {}

		/// \brief Constructs a copy
		constexpr size(size const&) = default;

		/// \brief Constructs a copy
		constexpr size(size&&) = default;

		/// \brief Constructs a size width width and height
		constexpr size(w_type const& width, h_type const& height):
			width_(width), height_(height) {}


		/// \brief Copy assignment
		constexpr size& operator=(size const&) = default;

		/// \brief Move assignment
		constexpr size& operator=(size&&) = default;


		/// \brief The width
		constexpr w_type& width(){
			return width_;
		}

		/// \brief The height
		constexpr h_type& height(){
			return height_;
		}


		/// \brief The width
		constexpr w_type const width()const{
			return width_;
		}

		/// \brief The height
		constexpr h_type const height()const{
			return height_;
		}


		/// \brief Set width and height
		constexpr void set(w_type const& width, h_type const& height){
			width_ = width;
			height_ = height;
		}


		/// \brief Get true, if width and height are positiv
		constexpr bool is_positive()const{
			return width() >= w_type() && height() >= h_type();
		}


		/// \brief Get width * height
		constexpr auto area()const{
			return width() * height();
		}

	private:
		w_type width_;
		h_type height_;
	};


	template < typename XT, typename YT >
	constexpr bool operator==(
		size< XT, YT > const& a,
		size< XT, YT > const& b
	){
		return a.width() == b.width() && a.height() == b.height();
	}

	template < typename XT, typename YT >
	constexpr bool operator!=(
		size< XT, YT > const& a,
		size< XT, YT > const& b
	){
		return !(a == b);
	}


	template < typename XT, typename YT >
	class point;

	template < typename XT, typename YT >
	point< XT, YT > to_point(size< XT, YT > const& s){
		return {s.width(), s.height()};
	}

	template < typename PXT, typename PYT = PXT, typename SXT, typename SYT >
	point< PXT, PYT > to_point(size< SXT, SYT > const& s){
		return {static_cast< PXT >(s.width()), static_cast< PYT >(s.height())};
	}


}

#endif
