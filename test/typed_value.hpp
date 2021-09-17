#pragma once


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
