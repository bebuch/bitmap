#pragma once

#include <cmath>
#include <cstdlib>
#include <type_traits>
#include <utility>


namespace bmp {


    namespace detail {


        template <typename WT, typename HT>
        struct size_base {};

        template <typename T>
        struct size_base<T, T> {
            /// \brief Type of width and height
            using value_type = T;
        };


    }


    /// \brief A class for manipulating sizes
    template <typename WT, typename HT = WT>
    class size: public detail::size_base<WT, HT> {
    public:
        /// \brief Type of the width
        using w_type = WT;

        /// \brief Type of the height
        using h_type = HT;


        /// \brief Constructs a size with width 0 and height 0
        constexpr size()
            : width_()
            , height_() {}

        /// \brief Constructs a copy
        constexpr size(size const&) = default;

        /// \brief Constructs a copy
        constexpr size(size&&) = default;

        /// \brief Constructs a size width width and height
        constexpr size(w_type width, h_type height)
            : width_(std::move(width))
            , height_(std::move(height)) {}


        /// \brief Enable static casts
        template <typename W2T, typename H2T>
        explicit constexpr operator size<W2T, H2T>() const {
            return {static_cast<W2T>(width_), static_cast<H2T>(height_)};
        }


        /// \brief Copy assignment
        constexpr size& operator=(size const&) = default;

        /// \brief Move assignment
        constexpr size& operator=(size&&) = default;


        /// \brief The width
        [[nodiscard]] constexpr w_type& width() {
            return width_;
        }

        /// \brief The height
        [[nodiscard]] constexpr h_type& height() {
            return height_;
        }


        /// \brief The width
        [[nodiscard]] constexpr w_type const& width() const {
            return width_;
        }

        /// \brief The height
        [[nodiscard]] constexpr h_type const& height() const {
            return height_;
        }


        /// \brief Set width and height
        constexpr void set(w_type width, h_type height) {
            width_ = std::move(width);
            height_ = std::move(height);
        }


        /// \brief Get true, if width and height are positiv
        [[nodiscard]] constexpr bool is_positive() const {
            return width() >= w_type() && height() >= h_type();
        }


        /// \brief Get width * height
        [[nodiscard]] constexpr auto area() const {
            using common_type = std::common_type_t<w_type, h_type>;

            auto convert = [](auto const& v) {
                using type = std::remove_reference_t<decltype(v)>;
                if constexpr(std::is_signed_v<type>) {
                    using std::abs;
                    return static_cast<common_type>(abs(v));
                } else {
                    return static_cast<common_type>(v);
                }
            };
            return convert(width()) * convert(height());
        }

    private:
        w_type width_;
        h_type height_;
    };


    template <typename WT, typename HT>
    [[nodiscard]] constexpr bool operator==(size<WT, HT> const& a, size<WT, HT> const& b) {
        return a.width() == b.width() && a.height() == b.height();
    }

    template <typename WT, typename HT>
    [[nodiscard]] constexpr bool operator!=(size<WT, HT> const& a, size<WT, HT> const& b) {
        return !(a == b);
    }


    template <typename XT, typename YT>
    class point;

    template <typename WT, typename HT>
    [[nodiscard]] point<WT, HT> to_point(size<WT, HT> const& s) {
        return {s.width(), s.height()};
    }

    template <typename XT, typename YT = XT, typename WT, typename HT>
    [[nodiscard]] point<XT, YT> to_point(size<WT, HT> const& s) {
        return {static_cast<XT>(s.width()), static_cast<YT>(s.height())};
    }


}
