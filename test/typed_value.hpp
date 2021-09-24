#pragma once

#include <limits>
#include <type_traits>


template <std::size_t N>
class typed_value {
public:
    constexpr typed_value()
        : v(0) {}

    explicit constexpr typed_value(int v)
        : v(v) {}

    constexpr typed_value(typed_value const&) = default;

    constexpr typed_value& operator=(typed_value const&) = default;

    [[nodiscard]] auto operator<=>(const typed_value<N>&) const = default;

    constexpr typed_value& operator+=(typed_value const& a){
        v += a.v;
        return *this;
    }

    constexpr typed_value& operator-=(typed_value const& a){
        v -= a.v;
        return *this;
    }

    constexpr typed_value& operator*=(typed_value const& a){
        v *= a.v;
        return *this;
    }

    constexpr typed_value& operator/=(typed_value const& a){
        v /= a.v;
        return *this;
    }

    constexpr typed_value& operator%=(typed_value const& a){
        v %= a.v;
        return *this;
    }

    constexpr typed_value operator+(){
        return *this;
    }

    constexpr typed_value operator-(){
        return typed_value(-v);
    }


private:
    int v;
};


template <std::size_t N>
[[nodiscard]] constexpr typed_value<N> operator+(typed_value<N> a, typed_value<N> const& b){
    return a += b;
}

template <std::size_t N>
[[nodiscard]] constexpr typed_value<N> operator-(typed_value<N> a, typed_value<N> const& b){
    return a -= b;
}

template <std::size_t N>
[[nodiscard]] constexpr typed_value<N> operator*(typed_value<N> a, typed_value<N> const& b){
    return a *= b;
}

template <std::size_t N>
[[nodiscard]] constexpr typed_value<N> operator/(typed_value<N> a, typed_value<N> const& b){
    return a /= b;
}

template <std::size_t N>
[[nodiscard]] constexpr typed_value<N> operator%(typed_value<N> a, typed_value<N> const& b){
    return a %= b;
}

constexpr auto operator ""_tv0(unsigned long long v){
    return typed_value<0>{static_cast<int>(v)};
}

constexpr auto operator ""_tv1(unsigned long long v){
    return typed_value<1>{static_cast<int>(v)};
}

constexpr auto operator ""_tv2(unsigned long long v){
    return typed_value<2>{static_cast<int>(v)};
}

constexpr auto operator ""_tv3(unsigned long long v){
    return typed_value<3>{static_cast<int>(v)};
}

template <std::size_t N>
struct std::numeric_limits<typed_value<N>>: std::numeric_limits<int>{
    static constexpr typed_value<N> min() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::min());
    }

    static constexpr typed_value<N> max() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::max());
    }

    static constexpr typed_value<N> lowest() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::lowest());
    }

    static constexpr typed_value<N> epsilon() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::epsilon());
    }

    static constexpr typed_value<N> round_error() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::round_error());
    }

    static constexpr typed_value<N> infinity() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::infinity());
    }

    static constexpr typed_value<N> quiet_NaN() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::quiet_NaN());
    }

    static constexpr typed_value<N> signaling_NaN() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::signaling_NaN());
    }

    static constexpr typed_value<N> denorm_min() noexcept {
        return typed_value<N>(::std::numeric_limits<int>::denorm_min());
    }
};

static_assert(std::numeric_limits<typed_value<0>>::is_specialized);
static_assert(std::numeric_limits<typed_value<0>>::is_integer);
