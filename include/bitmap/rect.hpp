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
        using w_type = WT;

        /// \brief Type of the height
        using h_type = HT;

        /// \brief Type of the rect top left position
        using pos_type = ::bmp::point<XT, YT>;

        /// \brief Type of the rect size
        using size_type = ::bmp::size<WT, HT>;


        /// \brief Constructs a blank rect
        constexpr rect_base() = default;

        /// \brief Copy constructor
        constexpr rect_base(rect_base const&) = default;

        /// \brief Move constuctor
        constexpr rect_base(rect_base&&) = default;

        /// \brief Constructs on position (top_left.x, top_left.y), with size (size.w, size.h)
        constexpr rect_base(pos_type top_left, size_type size)
            : top_left_(std::move(top_left))
            , size_(std::move(size)) {}

        /// \brief Constructs on position (0, 0), with size (size.w, size.h)
        constexpr rect_base(size_type size)
            : size_(std::move(size)) {}

        /// \brief Constructs on position (0, 0), with size (w, h)
        constexpr rect_base(w_type w, h_type h)
            : size_(std::move(w), std::move(h)) {}

        /// \brief Constructs on position (x, y), with size (w, h)
        constexpr rect_base(x_type x, w_type w, y_type y, h_type h)
            : top_left_(std::move(x), std::move(y))
            , size_(std::move(w), std::move(h)) {}


        /// \brief Copy assignment
        constexpr rect_base& operator=(rect_base const&) = default;

        /// \brief Move assignment
        constexpr rect_base& operator=(rect_base&&) = default;


        /// \brief Get true, if width or height is zero
        [[nodiscard]] constexpr bool is_empty() const {
            return w() == w_type() && h() == h_type();
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
        [[nodiscard]] constexpr w_type const& w() const {
            return size_.w();
        }

        /// \brief Get the height
        [[nodiscard]] constexpr h_type const& h() const {
            return size_.h();
        }


        /// \brief Get abs(w) * abs(h)
        [[nodiscard]] constexpr auto area() const {
            return size_.area();
        }

        /// \brief Get abs(w) * abs(h)
        template <typename CommonType>
        [[nodiscard]] constexpr CommonType area_as() const {
            return size_.template area_as<CommonType>();
        }


        /// \brief Set x, y, width and height
        constexpr void set(pos_type pos, size_type size) {
            set_pos(std::move(pos));
            set_size(std::move(size));
        }

        /// \brief Set x, y, width and height
        constexpr void set(x_type x, w_type w, y_type y, h_type h) {
            set_pos(std::move(x), std::move(y));
            set_size(std::move(w), std::move(h));
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
        constexpr void set_size(w_type w, h_type h) {
            set_size({std::move(w), std::move(h)});
        }

        /// \brief Set the x position
        constexpr void set_x(x_type x) {
            top_left_.set_x(std::move(x));
        }

        /// \brief Set the y position
        constexpr void set_y(y_type y) {
            top_left_.set_y(std::move(y));
        }

        /// \brief Set the width
        constexpr void set_w(w_type w) {
            size_.set_w(std::move(w));
        }

        /// \brief Set the height
        constexpr void set_h(h_type h) {
            size_.set_h(std::move(h));
        }


        /// \brief Moves the rect in horizontal direction
        constexpr void move(x_type const& x_translation, y_type const& y_translation) {
            top_left_ += pos_type(x_translation, y_translation);
        }

        /// \brief Moves the rect in horizontal direction
        constexpr void move(pos_type const& translation) {
            top_left_ += pos_type(translation, translation);
        }

        /// \brief Moves the rect in horizontal direction
        constexpr void move_horizontally(x_type const& translation) {
            top_left_ += pos_type(translation, y_type());
        }

        /// \brief Moves the rect in vertical direction
        constexpr void move_vertically(y_type const& translation) {
            top_left_ += pos_type(x_type(), translation);
        }


        [[nodiscard]] constexpr bool operator==(rect_base const&) const = default;


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
    rect(XT, WT, YT, HT) -> rect<XT, WT, YT, HT>;

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


    /// \brief Get a rect that contains both rects
    template <typename XT, typename YT>
    [[nodiscard]] constexpr auto join(
        rect<XT, XT, YT, YT> const& l,
        rect<XT, XT, YT, YT> const& r
    ) {
        return rect<XT, XT, YT, YT>(
            point<XT, YT>(std::min(l.left(), r.left()), std::min(l.top(), r.top())),
            point<XT, YT>(std::max(l.right(), r.right()), std::max(l.bottom(), r.bottom())));
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
        ///        bottom_right.x + 1 as width and rb.y + 1 as height
        constexpr rect_hv_base(pos_type const& rb)
            : rect_base<XT, XT, YT, YT>(to_size(
                pos_type(horizontal_type(1), vertical_type(1)) + rb)) {}

        /// \brief Constructs a rect on position (top_left.x, top_left.y), with
        ///        size bottom_right.x + 1 - top_left.x as width and
        ///        bottom_right.y + 1 - top_left.x as height
        constexpr rect_hv_base(pos_type const& lt, pos_type const& rb)
            : rect_base<XT, XT, YT, YT>(lt, to_size(
                pos_type(horizontal_type(1), vertical_type(1)) + rb - lt))
            {}


        using rect_base<XT, XT, YT, YT>::x;
        using rect_base<XT, XT, YT, YT>::y;
        using rect_base<XT, XT, YT, YT>::w;
        using rect_base<XT, XT, YT, YT>::h;
        using rect_base<XT, XT, YT, YT>::pos;
        using rect_base<XT, XT, YT, YT>::size;

        using rect_base<XT, XT, YT, YT>::set_x;
        using rect_base<XT, XT, YT, YT>::set_y;
        using rect_base<XT, XT, YT, YT>::set_w;
        using rect_base<XT, XT, YT, YT>::set_h;
        using rect_base<XT, XT, YT, YT>::set_pos;
        using rect_base<XT, XT, YT, YT>::set_size;


        /// \brief Get the top point
        [[nodiscard]] constexpr vertical_type t() const {
            return y();
        }

        /// \brief Get the bottom point
        [[nodiscard]] constexpr vertical_type b() const {
            return h() + y() - vertical_type(1);
        }

        /// \brief Get the left point
        [[nodiscard]] constexpr horizontal_type l() const {
            return x();
        }

        /// \brief Get the right point
        [[nodiscard]] constexpr horizontal_type r() const {
            return w() + x() - horizontal_type(1);
        }


        /// \brief Get the top left corner
        [[nodiscard]] constexpr pos_type lt() const {
            return pos();
        }

        /// \brief Get the top right corner
        [[nodiscard]] constexpr pos_type rt() const {
            return {r(), t()};
        }

        /// \brief Get the bottom left corner
        [[nodiscard]] constexpr pos_type lb() const {
            return {l(), b()};
        }

        /// \brief Get the bottom right corner
        [[nodiscard]] constexpr pos_type rb() const {
            return {r(), b()};
        }


        /// \brief Set the top point
        constexpr void set_t(vertical_type const& t) {
            set_h(h() + y() - t);
            set_y(t);
        }

        /// \brief Set the bottom point
        constexpr void set_b(vertical_type const& b) {
            set_h(vertical_type(1) + b - y());
        }

        /// \brief Set the left point
        constexpr void set_l(horizontal_type const& l) {
            set_w(w() + x() - l);
            set_x(l);
        }

        /// \brief Set the right point
        constexpr void set_r(horizontal_type const& r) {
            set_w(horizontal_type(1) + r - x());
        }


        /// \brief Set the top left corner
        constexpr void set_lt(pos_type const& lt) {
            set_l(lt.x());
            set_t(lt.y());
        }

        /// \brief Set the top right corner
        constexpr void set_rt(pos_type const& rt) {
            set_r(rt.x());
            set_t(rt.y());
        }

        /// \brief Set the bottom left corner
        constexpr void set_lb(pos_type const& lb) {
            set_l(lb.x());
            set_b(lb.y());
        }

        /// \brief Set the bottom right corner
        constexpr void set_rb(pos_type const& rb) {
            set_r(rb.x());
            set_b(rb.y());
        }
    };


}
