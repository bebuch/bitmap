#pragma once

#include <utility>


namespace bmp {


    namespace detail {


        template <typename XT, typename YT>
        struct point_base {};

        template <typename T>
        struct point_base<T, T> {
            /// \brief Type of the positions
            using value_type = T;
        };


    }


    /// \brief A class for representing points
    /// \tparam XT Type of the x position data
    /// \tparam YT Type of the y position data
    template <typename XT, typename YT = XT>
    class point: public detail::point_base<XT, YT> {
    public:
        /// \brief Type of the x positions
        using x_type = XT;

        /// \brief Type of the y positions
        using y_type = YT;


        /// \brief Constructs a point by (0, 0)
        constexpr point()
            : x_()
            , y_() {}

        /// \brief Copy constructor
        constexpr point(point const&) = default;

        /// \brief Move constructor
        constexpr point(point&&) = default;

        /// \brief Constructs a point by (x, y)
        constexpr point(x_type x, y_type y)
            : x_(std::move(x))
            , y_(std::move(y)) {}


        /// \brief Enable static casts
        template <typename X2T, typename Y2T>
        [[nodiscard]] explicit constexpr operator point<X2T, Y2T>() const {
            return {static_cast<X2T>(x_), static_cast<Y2T>(y_)};
        }


        /// \brief Copy assignment
        constexpr point& operator=(point const&) = default;

        /// \brief Move assignment
        constexpr point& operator=(point&&) = default;


        /// \brief The x
        [[nodiscard]] constexpr x_type& x() {
            return x_;
        }

        /// \brief The y
        [[nodiscard]] constexpr y_type& y() {
            return y_;
        }


        /// \brief The x
        [[nodiscard]] constexpr x_type const& x() const {
            return x_;
        }

        /// \brief The y
        [[nodiscard]] constexpr y_type const& y() const {
            return y_;
        }


        /// \brief Set x and y
        constexpr void set(x_type x, y_type y) {
            x_ = std::move(x);
            y_ = std::move(y);
        }


        /// \brief Get true, if x and y are positiv
        [[nodiscard]] constexpr bool is_positive() const {
            return x() >= x_type() && y() >= y_type();
        }


    private:
        x_type x_;
        y_type y_;
    };


    template <typename XT, typename YT>
    [[nodiscard]] constexpr bool operator==(point<XT, YT> const& a, point<XT, YT> const& b) {
        return a.x() == b.x() && a.y() == b.y();
    }

    template <typename XT, typename YT>
    [[nodiscard]] constexpr bool operator!=(point<XT, YT> const& a, point<XT, YT> const& b) {
        return !(a == b);
    }


    template <typename XT, typename YT>
    constexpr point<XT, YT>& operator+=(point<XT, YT>& a, point<XT, YT> const& b) {
        a.x() += b.x();
        a.y() += b.y();
        return a;
    }

    template <typename XT, typename YT>
    constexpr point<XT, YT>& operator-=(point<XT, YT>& a, point<XT, YT> const& b) {
        a.x() -= b.x();
        a.y() -= b.y();
        return a;
    }

    template <typename XT, typename YT>
    constexpr point<XT, YT>& operator*=(point<XT, YT>& a, point<XT, YT> const& b) {
        a.x() *= b.x();
        a.y() *= b.y();
        return a;
    }

    template <typename XT, typename YT>
    constexpr point<XT, YT>& operator/=(point<XT, YT>& a, point<XT, YT> const& b) {
        a.x() /= b.x();
        a.y() /= b.y();
        return a;
    }

    template <typename XT, typename YT>
    constexpr point<XT, YT>& operator%=(point<XT, YT>& a, point<XT, YT> const& b) {
        a.x() %= b.x();
        a.y() %= b.y();
        return a;
    }


    template <typename XT, typename YT>
    [[nodiscard]] constexpr point<XT, YT> operator+(point<XT, YT> a, point<XT, YT> const& b) {
        return a += b;
    }

    template <typename XT, typename YT>
    [[nodiscard]] constexpr point<XT, YT> operator-(point<XT, YT> a, point<XT, YT> const& b) {
        return a -= b;
    }

    template <typename XT, typename YT>
    [[nodiscard]] constexpr point<XT, YT> operator*(point<XT, YT> a, point<XT, YT> const& b) {
        return a *= b;
    }

    template <typename XT, typename YT>
    [[nodiscard]] constexpr point<XT, YT> operator/(point<XT, YT> a, point<XT, YT> const& b) {
        return a /= b;
    }

    template <typename XT, typename YT>
    [[nodiscard]] constexpr point<XT, YT> operator%(point<XT, YT> a, point<XT, YT> const& b) {
        return a %= b;
    }


    template <typename WT, typename HT>
    class size;

    template <typename XT, typename YT>
    [[nodiscard]] size<XT, YT> to_size(point<XT, YT> const& p) {
        return {p.x(), p.y()};
    }

    template <typename WT, typename HT = WT, typename XT, typename YT>
    [[nodiscard]] size<WT, HT> to_size(point<XT, YT> const& p) {
        return {static_cast<WT>(p.x()), static_cast<HT>(p.y())};
    }


}
