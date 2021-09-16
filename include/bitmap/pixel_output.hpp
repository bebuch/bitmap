#pragma once

#include "pixel.hpp"

#include <ostream>


namespace bmp::pixel {


    template <typename T>
    std::ostream& operator<<(std::ostream& os, basic_ga<T> const& v) {
        if constexpr(
            std::is_same_v<
                T,
                char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) {
            return os << '{' << static_cast<int>(v.g) << ", " << static_cast<int>(v.a) << '}';
        } else {
            return os << '{' << v.g << ", " << v.a << '}';
        }
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, basic_rgb<T> const& v) {
        if constexpr(
            std::is_same_v<
                T,
                char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) {
            return os << '{' << static_cast<int>(v.r) << ", " << static_cast<int>(v.g) << ", "
                      << static_cast<int>(v.b) << '}';
        } else {
            return os << '{' << v.r << ", " << v.g << ", " << v.b << '}';
        }
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, basic_rgba<T> const& v) {
        if constexpr(
            std::is_same_v<
                T,
                char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) {
            return os << '{' << static_cast<int>(v.r) << ", " << static_cast<int>(v.g) << ", "
                      << static_cast<int>(v.b) << ", " << static_cast<int>(v.a) << '}';
        } else {
            return os << '{' << v.r << ", " << v.g << ", " << v.b << ", " << v.a << '}';
        }
    }


}
