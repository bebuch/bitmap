//-----------------------------------------------------------------------------
// Copyright (c) 2009-2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__bitmap__hpp_INCLUDED_
#define _bitmap__bitmap__hpp_INCLUDED_

#include "point.hpp"
#include "size.hpp"

#include <vector>
#include <numeric>
#include <utility>
#include <stdexcept>
#include <sstream>


namespace bmp{


	/// \brief A bitmap for data manipulation
	/// \tparam T Type of the data that administrates the bitmap
	template < typename T >
	class bitmap{
	public:
		/// \brief Type of the data that administrates the bitmap
		using value_type = T;

		/// \brief Type of points in the bitmap
		using point_type = ::bmp::point< std::size_t >;

		/// \brief Type of bitmap size
		using size_type = ::bmp::size< std::size_t >;

		/// \brief Type of bitmap size as signed
		using ssize_type = ::bmp::size< std::ptrdiff_t >;

		/// \brief Type of a iterator for data
		using iterator = typename std::vector< value_type >::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator =
			typename std::vector< value_type >::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator =
			typename std::vector< value_type >::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator =
			typename std::vector< value_type >::const_reverse_iterator;

		/// \brief Type of a reference to data
		using reference = typename std::vector< value_type >::reference;

		/// \brief Type of a const reference to data
		using const_reference =
			typename std::vector< value_type >::const_reference;



		/// \brief Constructs a blank bitmap
		bitmap() = default;

		/// \brief Constructs a bitmap by copying another one
		bitmap(bitmap const&) = default;

		/// \brief Constructs a bitmap by moving the data of another one
		bitmap(bitmap&&) = default;

		/// \brief Constructs a bitmap on position (0, 0), with size size.width
		///        and size.height, initialiese all values with value
		/// \throw std::out_of_range
		bitmap(size_type const& size, value_type const& value = value_type()):
			size_(size),
			data_(point_count(), value)
		{
			throw_if_size_is_negative(size_);
		}

		/// \brief Constructs a bitmap on position (0, 0), with size size.width
		///        and size.height, initialiese all values with value
		/// \throw std::out_of_range
		template < typename InputIterator >
		bitmap(size_type const& size, InputIterator first, InputIterator last) :
			size_(size),
			data_(first, last)
		{
			throw_if_size_is_negative(size_);
			if (data_.size() != point_count()){
				throw std::logic_error(
					"bitmap constructor size (" +
					std::to_string(size_.width()) + "x" +
					std::to_string(size_.height()) +
					") and iterator range (" +
					std::to_string(data_.size()) +
					") are incompatible"
				);
			}
		}

		/// \brief Constructs a bitmap on position (0, 0), with size width and
		///        height, initialiese all values with value
		/// \throw std::out_of_range
		bitmap(
			std::size_t width, std::size_t height,
			value_type const& value = value_type()
		):
			size_(width, height),
			data_(point_count(), value)
		{
			throw_if_size_is_negative(size_);
		}


		/// \brief Standard destructor
		~bitmap() = default;


		/// \brief Copy assignment
		bitmap& operator=(bitmap const& bitmap) = default;

		/// \brief Move assignment
		bitmap& operator=(bitmap&& bitmap) = default;


		/// \brief Get a iterator on begin of the data
		iterator begin(){
			return data_.begin();
		}

		/// \brief Get a const_iterator on begin of the data
		const_iterator begin()const{
			return data_.begin();
		}

		/// \brief Get a const_iterator on begin of the data
		const_iterator cbegin()const{
			return data_.cbegin();
		}

		/// \brief Get a iterator behind the data
		iterator end(){
			return data_.end();
		}

		/// \brief Get a const_iterator behind the data
		const_iterator end()const{
			return data_.end();
		}

		/// \brief Get a const_iterator behind the data
		const_iterator cend()const{
			return data_.cend();
		}


		/// \brief Get a reverse_iterator on end of the data
		reverse_iterator rbegin(){
			return data_.rbegin();
		}

		/// \brief Get a const_reverse_iterator on end of the data
		const_reverse_iterator rbegin()const{
			return data_.rbegin();
		}

		/// \brief Get a const_reverse_iterator on end of the data
		const_reverse_iterator crbegin()const{
			return data_.crbegin();
		}

		/// \brief Get a reverse_iterator before the data
		reverse_iterator rend(){
			return data_.rend();
		}

		/// \brief Get a const_reverse_iterator before the data
		const_reverse_iterator rend()const{
			return data_.rend();
		}

		/// \brief Get a const_reverse_iterator before the data
		const_reverse_iterator crend()const{
			return data_.crend();
		}


		/// \brief Resize the data field
		/// \attention All pointers and iterators to the data become invalid
		void resize(
			std::size_t width, std::size_t height,
			value_type const& value = value_type()
		){
			resize(size_type(width, height), value);
		}

		/// \brief Resize the data field
		/// \attention All pointers and iterators to the data become invalid
		void resize(
			size_type const& size,
			value_type const& value = value_type()
		){
			throw_if_size_is_negative(size);
			data_.resize(size.area(), value);
			size_ = size;
		}


		/// \brief Get the width
		std::size_t width()const{
			return size_.width();
		}

		/// \brief Get the height
		std::size_t height()const{
			return size_.height();
		}

		/// \brief Get the size
		size_type const size()const{
			return size_;
		}

		/// \brief Get the number of points in the bitmap
		std::size_t point_count()const{
			return size_.area();
		}


		/// \brief Get the width as signed
		std::ptrdiff_t s_width()const{
			return static_cast< std::ptrdiff_t >(width());
		}

		/// \brief Get the height as signed
		std::ptrdiff_t s_height()const{
			return static_cast< std::ptrdiff_t >(height());
		}

		/// \brief Get the size as signed
		ssize_type const ssize()const{
			return ssize_type(s_width(), s_height());
		}

		/// \brief Get the number of points in the bitmap as signed
		std::ptrdiff_t s_point_count()const{
			return static_cast< std::ptrdiff_t >(point_count());
		}


		/// \brief Get the width with requested type
		template < typename U >
		U width_as()const{
			if(width() > this->max< U >()){
				throw std::runtime_error("width is to big for requested type");
			}
			return static_cast< U >(width());
		}

		/// \brief Get the height with requested type
		template < typename U >
		U height_as()const{
			if(height() > this->max< U >()){
				throw std::runtime_error("height is to big for requested type");
			}
			return static_cast< U >(height());
		}

		/// \brief Get the size with requested type
		template < typename U >
		::bmp::size< U > const size_as()const{
			return int_size_type(width_as< U >(), height_as< U >());
		}

		/// \brief Get the number of points in the bitmap with requested type
		template < typename U >
		U point_count_as()const{
			auto count = point_count();
			if(count > this->max< U >()){
				throw std::runtime_error(
					"point count is to big for requested type");
			}
			return static_cast< U >(count);
		}


		/// \brief Get a pointer to data for direct manipulation
		value_type* data(){
			return const_cast< value_type* >(
				static_cast< const bitmap< value_type >& >(*this).data());
		}

		/// \brief Get a pointer to constant data for direct read
		value_type const* data()const{
			return data_.empty() ? 0 : &data_[0];
		}


		/// \brief Get a reference to the value by local coordinates
		/// \throw std::out_of_range in debug build
		reference operator()(std::size_t x, std::size_t y) {
			return operator()(point_type(x, y));
		}

		/// \brief Get a reference to the value by local coordinates
		/// \throw std::out_of_range in debug build
		reference operator()(point_type const& point) {
			throw_if_out_of_range(point);
			return do_point(point);
		}

		/// \brief Get the value by local coordinates
		/// \throw std::out_of_range in debug build
		const_reference operator()(std::size_t x, std::size_t y)const {
			return operator()(point_type(x, y));
		}

		/// \brief Get the value by local coordinates
		/// \throw std::out_of_range in debug build
		const_reference operator()(point_type const& point)const{
			throw_if_out_of_range(point);
			return do_point(point);
		}


		/// \brief Converts a lokal point in a index for direct data access
		/// \attention This function performs no range protection
		std::size_t data_pos(std::size_t x, std::size_t y)const{
			return data_pos(point_type(x, y));
		}

		/// \brief Converts a lokal point in a index for direct data access
		/// \attention This function performs no range protection
		std::size_t data_pos(point_type const& point)const{
			return point.y() * width() + point.x();
		}


	protected:
		/// \brief The rectangle for global position and size
		size_type size_;

		/// \brief The data field
		std::vector< value_type > data_;


		/// \brief Get a point without range protection
		reference do_point(point_type const& point){
			return data_[data_pos(point)];
		}

		/// \brief Get a point without range protection
		const_reference do_point(point_type const& point)const{
			return data_[data_pos(point)];
		}

		/// \brief Throws an exception, if the point is out of range
		void throw_if_out_of_range(point_type const&
			#ifdef DEBUG
			point
			#endif
		)const{
			#ifdef DEBUG
				if(!is_point_in_bitmap(*this, point)){
					std::ostringstream os;
					os << "bitmap: point(x = " << point.x() << ", y = "
						<< point.y() << ") is outside the bitmap (width = "
						<< width() << ", height = " << height() << ")";
					throw std::out_of_range(os.str());
				}
			#endif
		}

		/// \brief Throws an exception if size is negative
		/// \throw std::out_of_range in debug build
		static void throw_if_size_is_negative(size_type const& size){
			if(!size.is_positive()){
				std::ostringstream os;
				os << "bitmap: bitmap obtain negative size{" << size.width()
					<< ", " << size.height() << "}";
				throw std::out_of_range(os.str());
			}
		}


	private:
		template < typename U >
		static constexpr std::size_t max()noexcept{
			return static_cast< std::size_t >(std::numeric_limits< U >::max());
		}
	};


	template < typename T >
	bool is_point_in_bitmap(
		bitmap< T > const& image,
		typename bitmap< T >::point_type const& point
	){
		if(
			point.x() <  0              ||
			point.x() >= image.width()  ||
			point.y() <  0              ||
			point.y() >= image.height()
		){
			return false;
		}
		return true;
	}


	/// \brief true, if size and contents are equal, otherwise false
	template < typename T >
	bool operator==(bitmap< T > const& l, bitmap< T > const& r){
		return l.size() == r.size()
			&& std::equal(l.begin(), l.end(), r.begin());
	}

	/// \brief true, if size and contents are not equal, otherwise false
	template < typename T >
	bool operator!=(bitmap< T > const& l, bitmap< T > const& r){
		return !(l == r);
	}


	/// \brief std::vector of bitmaps
	template < typename T >
	using bitmap_vector = std::vector< bitmap< T > >;


}

#endif
