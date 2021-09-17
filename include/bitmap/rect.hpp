#pragma once

#include "point.hpp"
#include "size.hpp"

#include <algorithm>


namespace bmp::detail {


    template <typename XT, typename WT, typename YT, typename HT>
    struct rect_common_base {};

    template <typename T>
    struct rect_common_base<T, T, T, T> {
        /// \brief Type of the x, y, width and height
        using value_type = T;
    };


    template <typename XT, typename WT, typename YT, typename HT>
    struct rect_base: rect_common_base<XT, WT, YT, HT> {
    public:
        /// \brief Type of the x position
        using x_type = XT;

        /// \brief Type of the y position
        using y_type = YT;

        /// \brief Type of the width
        using width_type = WT;

        /// \brief Type of the height
        using height_type = HT;

        /// \brief Type of the rect top left position
        using pos_type = ::bmp::point<XT, YT>;

        /// \brief Type of the rect size
        using size_type = ::bmp::size<WT, HT>;

        /// \brief Type of x, y, width and height
        using common_type =
            std::common_type_t<typename pos_type::common_type, typename size_type::common_type>;


        /// \brief Constructs a blank rect
        constexpr rect_base() = default;

        /// \brief Copy constructor
        constexpr rect_base(rect_base const&) = default;

        /// \brief Move constuctor
        constexpr rect_base(rect_base&&) = default;

        /// \brief Constructs a rect on position (top_left.x, top_left.y), with
        ///        size size.width and size.height
        constexpr rect_base(pos_type top_left, size_type size)
            : top_left_(std::move(top_left))
            , size_(std::move(size)) {}

        /// \brief Constructs a rect on position (0, 0), with size size.width
        ///        and size.height
        constexpr rect_base(size_type size)
            : size_(std::move(size)) {}

        /// \brief Constructs a rect on position (0, 0), with size width and
        ///        height
        constexpr rect_base(width_type width, height_type height)
            : size_(std::move(width), std::move(height)) {}

        /// \brief Constructs a rect on position (x, y), with size width and
        ///        height
        constexpr rect_base(x_type x, y_type y, width_type width, height_type height)
            : top_left_(std::move(x), std::move(y))
            , size_(std::move(width), std::move(height)) {}


        /// \brief Copy assignment
        constexpr rect_base& operator=(rect_base const&) = default;

        /// \brief Move assignment
        constexpr rect_base& operator=(rect_base&&) = default;


        /// \brief Get true, if width or height is zero
        [[nodiscard]] constexpr bool is_empty() const {
            return width() == width_type() && height() == height_type();
        }

        /// \brief Get true, if width and height are positv
        [[nodiscard]] constexpr bool is_positive() const {
            return size_.is_positive();
        }


        /// \brief Get the top left point
        [[nodiscard]] constexpr pos_type const& pos() const {
            return top_left_;
        }

        /// \brief Get the size
        [[nodiscard]] constexpr size_type const& size() const {
            return size_;
        }

        /// \brief Get the x position
        [[nodiscard]] constexpr x_type const& x() const {
            return top_left_.x();
        }

        /// \brief Get the y position
        [[nodiscard]] constexpr y_type const& y() const {
            return top_left_.y();
        }

        /// \brief Get the width
        [[nodiscard]] constexpr width_type const& width() const {
            return size_.width();
        }

        /// \brief Get the height
        [[nodiscard]] constexpr height_type const& height() const {
            return size_.height();
        }

        /// \brief Get width() * height()
        [[nodiscard]] constexpr auto area() const {
            return size_.area();
        }


        /// \brief Set x, y, width and height
        constexpr void set(pos_type pos, size_type size) {
            set_pos(std::move(pos));
            set_size(std::move(size));
        }

        /// \brief Set x, y, width and height
        constexpr void set(x_type x, y_type y, width_type width, height_type height) {
            set_pos({std::move(x), std::move(y)});
            set_size({std::move(width), std::move(height)});
        }

        /// \brief Set x and y
        constexpr void set_pos(pos_type pos) {
            top_left_ = std::move(pos);
        }

        /// \brief Set x and y
        constexpr void set_pos(x_type x, y_type y) {
            set_pos({std::move(x), std::move(y)});
        }

        /// \brief Set width and height
        constexpr void set_size(size_type size) {
            size_ = std::move(size);
        }

        /// \brief Set width and height
        constexpr void set_size(width_type width, height_type height) {
            set_size({std::move(width), std::move(height)});
        }

        /// \brief Set the x position
        constexpr void set_x(x_type x) {
            top_left_.x() = std::move(x);
        }

        /// \brief Set the y position
        constexpr void set_y(y_type y) {
            top_left_.y() = std::move(y);
        }

        /// \brief Set the width
        constexpr void set_width(width_type width) {
            size_.width() = std::move(width);
        }

        /// \brief Set the height
        constexpr void set_height(height_type height) {
            size_.height() = std::move(height);
        }


        /// \brief Moves the rect in horizontal direction
        constexpr void move(pos_type const& translation) {
            move_horizontally(translation.x);
            move_vertically(translation.y);
        }

        /// \brief Moves the rect in horizontal direction
        constexpr void move_horizontally(x_type const& translation) {
            top_left_.x() += translation;
        }

        /// \brief Moves the rect in vertical direction
        constexpr void move_vertically(y_type const& translation) {
            top_left_.y() += translation;
        }


    private:
        /// \brief The point in the top left corner
        pos_type top_left_;

        /// \brief The point in the bottom right corner
        size_type size_;
    };


    template <typename XT, typename WT, typename YT, typename HT>
    struct rect_hv_base: rect_base<XT, WT, YT, HT> {
        using rect_base<XT, WT, YT, HT>::rect_base;
    };


}


namespace bmp{


    /// \brief A class for manipulating rectangles
    template <typename XT, typename WT = XT, typename YT = XT, typename HT = WT>
    struct rect: detail::rect_hv_base<XT, WT, YT, HT>{
        using detail::rect_hv_base<XT, WT, YT, HT>::rect_hv_base;

        using detail::rect_hv_base<XT, WT, YT, HT>::pos;
        using detail::rect_hv_base<XT, WT, YT, HT>::size;

        /// \brief Enable static casts
        template <typename X2T, typename W2T, typename Y2T, typename H2T>
        [[nodiscard]] explicit constexpr operator rect<X2T, W2T, Y2T, H2T>() const {
            return {
                static_cast<::bmp::point<X2T, Y2T>>(pos()),
                static_cast<::bmp::size<W2T, H2T>>(size())};
        }
    };


    template <typename XT, typename WT, typename YT, typename HT>
    rect(XT, YT, WT, HT) -> rect<XT, WT, YT, HT>;

    template <typename XT, typename WT, typename YT, typename HT>
    rect(point<XT, YT>, size<WT, HT>) -> rect<XT, WT, YT, HT>;

    template <typename WT, typename HT>
    rect(WT, HT) -> rect<WT, WT, HT, HT>;

    template <typename WT, typename HT>
    rect(size<WT, HT>) -> rect<WT, WT, HT, HT>;

    template <typename XT, typename YT>
    rect(point<XT, YT>) -> rect<XT, XT, YT, YT>;

    template <typename XT, typename YT>
    rect(point<XT, YT>, point<XT, YT>) -> rect<XT, XT, YT, YT>;


    /// \brief true, if the rectangles are identical; false otherwise
    template <typename XT, typename WT, typename YT, typename HT>
    [[nodiscard]] constexpr bool operator==(
        rect<XT, WT, YT, HT> const& l,
        rect<XT, WT, YT, HT> const& r
    ) {
        return l.pos() == r.pos() && l.size() == r.size();
    }

    /// \brief false, if the rectangles are identical; true otherwise
    template <typename XT, typename WT, typename YT, typename HT>
    [[nodiscard]] constexpr bool operator!=(
        rect<XT, WT, YT, HT> const& l,
        rect<XT, WT, YT, HT> const& r
    ) {
        return !(l == r);
    }


    /// \brief Get a rect that contains both rects
    template <typename XT, typename WT, typename YT, typename HT>
    [[nodiscard]] constexpr auto join(
        rect<XT, WT, YT, HT> const& l,
        rect<XT, WT, YT, HT> const& r
    ) {
        return rect<XT, YT, WT, HT>(
            point<XT, YT>(std::min(l.left(), r.left()), std::min(l.top(), r.top())),
            point<XT, YT>(std::max(l.right(), r.right()), std::max(l.bottom(), r.bottom())));
    }


    /// \brief Get true, if point is in rect
    template <typename XT, typename WT, typename YT, typename HT, typename PXT, typename PYT>
    [[nodiscard]] constexpr bool contains(
        rect<XT, WT, YT, HT> const& rect,
        point<PXT, PYT> const& point
    ) {
        return point.x() >= rect.left() && point.y() >= rect.top() && point.x() < rect.right()
            && point.y() < rect.bottom();
    }

    /// \brief Get true, if test is in ref
    template <typename XT, typename WT, typename YT, typename HT>
    [[nodiscard]] constexpr bool contains(
        rect<XT, WT, YT, HT> const& ref,
        rect<XT, WT, YT, HT> const& test
    ) {
        return test.left() >= ref.left() && test.top() >= ref.top()
            && test.right() <= ref.right() && test.bottom() <= ref.bottom();
    }


}


namespace bmp::detail {


    template <typename XT, typename YT>
    struct rect_hv_base<XT, XT, YT, YT>: rect_base<XT, XT, YT, YT> {
        using typename rect_base<XT, XT, YT, YT>::pos_type;
        using typename rect_base<XT, XT, YT, YT>::size_type;

        /// \brief Type of the x and width
        using horizontal_type = XT;

        /// \brief Type of the y and height
        using vertical_type = YT;


        using rect_base<XT, XT, YT, YT>::rect_base;


        /// \brief Constructs a rect on position (0, 0), with size
        ///        bottom_right.x + 1 as width and bottom_right.y + 1 as height
        constexpr rect_hv_base(pos_type const& bottom_right)
            : rect_base<XT, XT, YT, YT>(to_size(bottom_right + pos_type(1, 1))) {}

        /// \brief Constructs a rect on position (top_left.x, top_left.y), with
        ///        size bottom_right.x + 1 - top_left.x as width and
        ///        bottom_right.y + 1 - top_left.x as height
        constexpr rect_hv_base(pos_type const& top_left, pos_type const& bottom_right)
            : rect_base<XT, XT, YT, YT>(top_left, to_size(bottom_right + pos_type(1, 1) - top_left))
            {}


        using rect_base<XT, XT, YT, YT>::x;
        using rect_base<XT, XT, YT, YT>::y;
        using rect_base<XT, XT, YT, YT>::width;
        using rect_base<XT, XT, YT, YT>::height;
        using rect_base<XT, XT, YT, YT>::pos;
        using rect_base<XT, XT, YT, YT>::size;


        /// \brief Get the top point
        [[nodiscard]] constexpr horizontal_type const top() const {
            return y();
        }

        /// \brief Get the bottom point
        [[nodiscard]] constexpr horizontal_type const bottom() const {
            return height() + y() - 1;
        }

        /// \brief Get the left point
        [[nodiscard]] constexpr vertical_type const left() const {
            return x();
        }

        /// \brief Get the right point
        [[nodiscard]] constexpr vertical_type const right() const {
            return width() + x() - 1;
        }


        /// \brief Get the top left corner
        [[nodiscard]] constexpr pos_type const top_left() const {
            return pos();
        }

        /// \brief Get the top right corner
        [[nodiscard]] constexpr pos_type const top_right() const {
            return {right(), top()};
        }

        /// \brief Get the bottom left corner
        [[nodiscard]] constexpr pos_type const bottom_left() const {
            return {left(), bottom()};
        }

        /// \brief Get the bottom right corner
        [[nodiscard]] constexpr pos_type const bottom_right() const {
            return {right(), bottom()};
        }


        /// \brief Set the top point
        constexpr void set_top(horizontal_type const& top) {
            set_y(top);
        }

        /// \brief Set the bottom point
        constexpr void set_bottom(horizontal_type const& bottom) {
            set_height(bottom + 1 - y());
        }

        /// \brief Set the left point
        constexpr void set_left(vertical_type const& left) {
            set_x(left);
        }

        /// \brief Set the right point
        constexpr void set_right(vertical_type const& right) {
            set_width(right + 1 - x());
        }


        /// \brief Set the top left corner
        constexpr void set_top_left(pos_type const& top_left) {
            set_pos(top_left);
        }

        /// \brief Set the top right corner
        constexpr void set_top_right(pos_type const& top_right) {
            set_right(top_right.x());
            set_top(top_right.y());
        }

        /// \brief Set the bottom left corner
        constexpr void set_bottom_left(pos_type const& bottom_left) {
            set_left(bottom_left.x());
            set_bottom(bottom_left.y());
        }

        /// \brief Set the bottom right corner
        constexpr void set_bottom_right(pos_type const& bottom_right) {
            set_right(bottom_right.x());
            set_bottom(bottom_right.y());
        }
    };


}
