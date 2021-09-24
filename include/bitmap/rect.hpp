#pragma once

#include "point.hpp"
#include "size.hpp"

#include <algorithm>
#include <type_traits>


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
        constexpr rect_base(pos_type const& top_left, size_type const& size)
            : top_left_(top_left)
            , size_(size) {}

        /// \brief Constructs on position (0, 0), with size (size.w, size.h)
        constexpr rect_base(size_type const& size)
            : size_(size) {}

        /// \brief Constructs on position (0, 0), with size (w, h)
        constexpr rect_base(w_type const& w, h_type const& h)
            : size_(w, h) {}

        /// \brief Constructs on position (x, y), with size (w, h)
        constexpr rect_base(x_type const& x, w_type const& w, y_type const& y, h_type const& h)
            : top_left_(x, y)
            , size_(w, h) {}


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
        [[nodiscard]] constexpr pos_type pos() const {
            return top_left_;
        }

        /// \brief Get the size
        [[nodiscard]] constexpr size_type size() const {
            return size_;
        }

        /// \brief Get the x position
        [[nodiscard]] constexpr x_type x() const {
            return top_left_.x();
        }

        /// \brief Get the y position
        [[nodiscard]] constexpr y_type y() const {
            return top_left_.y();
        }

        /// \brief Get the width
        [[nodiscard]] constexpr w_type w() const {
            return size_.w();
        }

        /// \brief Get the height
        [[nodiscard]] constexpr h_type h() const {
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
        constexpr void set(pos_type const& pos, size_type const& size) {
            set_pos(pos);
            set_size(size);
        }

        /// \brief Set x, y, width and height
        constexpr void set(x_type const& x, w_type const& w, y_type const& y, h_type const& h) {
            set_pos(x, y);
            set_size(w, h);
        }

        /// \brief Set x and y
        constexpr void set_pos(pos_type const& pos) {
            top_left_ = pos;
        }

        /// \brief Set x and y
        constexpr void set_pos(x_type const& x, y_type const& y) {
            set_pos({x, y});
        }

        /// \brief Set width and height
        constexpr void set_size(size_type const& size) {
            size_ = size;
        }

        /// \brief Set width and height
        constexpr void set_size(w_type const& w, h_type const& h) {
            set_size({w, h});
        }

        /// \brief Set the x position
        constexpr void set_x(x_type const& x) {
            top_left_.set_x(x);
        }

        /// \brief Set the y position
        constexpr void set_y(y_type const& y) {
            top_left_.set_y(y);
        }

        /// \brief Set the width
        constexpr void set_w(w_type const& w) {
            size_.set_w(w);
        }

        /// \brief Set the height
        constexpr void set_h(h_type const& h) {
            size_.set_h(h);
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

        /// \brief Enable static casts
        template <typename X2T, typename W2T = X2T, typename Y2T = X2T, typename H2T = W2T>
        [[nodiscard]] explicit constexpr operator rect<X2T, W2T, Y2T, H2T>() const {
            return {
                static_cast<point<X2T, Y2T>>(detail::rect_hv_base<XT, WT, YT, HT>::pos()),
                static_cast<size<W2T, H2T>>(detail::rect_hv_base<XT, WT, YT, HT>::size())};
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


    /// \brief Get true, if point is in rect
    template <typename XT, typename YT>
    [[nodiscard]] constexpr bool contains(
        rect<XT, XT, YT, YT> const& rect,
        point<XT, YT> const& point
    ) {
        return point.x() >= rect.l() && point.x() <= rect.r()
            && point.y() >= rect.t() && point.y() <= rect.b();
    }

    /// \brief Get true, if test is in ref
    template <typename XT, typename YT>
    [[nodiscard]] constexpr bool contains(
        rect<XT, XT, YT, YT> const& ref,
        rect<XT, XT, YT, YT> const& test
    ) {
        return test.l() >= ref.l() && test.r() <= ref.r()
            && test.t() >= ref.t() && test.b() <= ref.b();
    }


    /// \brief Get a rect that contains both rects
    template <typename XT, typename YT>
    [[nodiscard]] constexpr rect<XT, XT, YT, YT> join(
        rect<XT, XT, YT, YT> const& l,
        rect<XT, XT, YT, YT> const& r
    ) {
        using std::min;
        using std::max;
        return {
            ::bmp::point(min(l.l(), r.l()), min(l.t(), r.t())),
            ::bmp::point(max(l.r(), r.r()), max(l.b(), r.b()))};
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

        /// \brief true if x dimensions are integer types, false otherwise
        static constexpr bool is_x_half_open = std::numeric_limits<horizontal_type>::is_integer;

        /// \brief true if y dimensions are integer types, false otherwise
        static constexpr bool is_y_half_open = std::numeric_limits<vertical_type>::is_integer;


        using rect_base<XT, XT, YT, YT>::rect_base;


        /// \brief Constructs a rect on position (0, 0), with size
        ///        bottom_right.x + 1 as width and rb.y + 1 as height
        constexpr rect_hv_base(pos_type const& rb)
            : rect_base<XT, XT, YT, YT>(to_size(pos_type(
                static_cast<horizontal_type>(is_x_half_open),
                static_cast<vertical_type>(is_y_half_open)) + rb)) {}

        /// \brief Constructs a rect on position (top_left.x, top_left.y), with
        ///        size bottom_right.x + 1 - top_left.x as width and
        ///        bottom_right.y + 1 - top_left.x as height
        constexpr rect_hv_base(pos_type const& lt, pos_type const& rb)
            : rect_base<XT, XT, YT, YT>(lt, to_size(pos_type(
                static_cast<horizontal_type>(is_x_half_open),
                static_cast<vertical_type>(is_y_half_open)) + rb - lt))
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
            return h() + y() - static_cast<vertical_type>(is_y_half_open);
        }

        /// \brief Get the left point
        [[nodiscard]] constexpr horizontal_type l() const {
            return x();
        }

        /// \brief Get the right point
        [[nodiscard]] constexpr horizontal_type r() const {
            return w() + x() - static_cast<horizontal_type>(is_x_half_open);
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
            set_h(static_cast<vertical_type>(is_y_half_open) + b - y());
        }

        /// \brief Set the left point
        constexpr void set_l(horizontal_type const& l) {
            set_w(w() + x() - l);
            set_x(l);
        }

        /// \brief Set the right point
        constexpr void set_r(horizontal_type const& r) {
            set_w(static_cast<horizontal_type>(is_x_half_open) + r - x());
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
