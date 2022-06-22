#pragma once

#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>


namespace bmp::detail {


    template <typename T>
    concept endian_supporting = std::intergral<T> || std::same_as<T, float> || std::same_as<T, double>;

    template <endian_supporting T>
    constexpr T byteswap(T const value) noexcept {
        if constexpr(std::intergral<T>){
            return std::byteswap(value);
        }else if constexpr(std::same_as<T, float>){
            return std::bit_cast<T>(std::byteswap(std::bit_cast<std::uint32_t>(value)));
        }else{
            return std::bit_cast<T>(std::byteswap(std::bit_cast<std::uint64_t>(value)));
        }
    }

    template <endian_supporting T>
    constexpr T native_to_big(T const value) noexcept {
        if constexpr(std::endian::big == std::endian::native){
            return value;
        }else{
            return byteswap(value);
        }
    }

    template <endian_supporting T>
    constexpr T big_to_native(T const value) noexcept {
        if constexpr(std::endian::big == std::endian::native){
            return value;
        }else{
            return byteswap(value);
        }
    }


    constexpr std::uint32_t big_io_magic = native_to_big(std::uint32_t(0x62626621));

    enum class binary_type_flags : std::uint8_t {
        is_unsigned = 0x00,
        is_signed = 0x01,
        is_floating_point = 0x02,
        is_bool = 0x03
    };

    enum class binary_endian_flags : std::uint8_t { is_big_endian = 0x00, is_little_endian = 0x10 };

    // clang-format off
    template <typename T>
    constexpr std::uint8_t binary_io_flags_v
        = static_cast<std::uint8_t>(std::is_same_v<T, bool>
            ? binary_type_flags::is_bool
            : std::is_floating_point_v<T>
            ? binary_type_flags::is_floating_point
            : std::is_signed_v<T>
            ? binary_type_flags::is_signed
            : binary_type_flags::is_unsigned)
        | static_cast<std::uint8_t>(std::endian::big == std::endian::native
            ? binary_endian_flags::is_big_endian
            : binary_endian_flags::is_little_endian);
    // clang-format on


}
