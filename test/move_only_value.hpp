#pragma once


template <std::size_t N>
class move_only_value {
public:
    constexpr move_only_value()
        : v(0) {}

    explicit constexpr move_only_value(int v)
        : v(v) {}

    explicit constexpr move_only_value(move_only_value&& o)
        : v(o.v)
    {
        o.v = 0;
    }

    constexpr move_only_value& operator=(move_only_value&& o) {
        v = o.v;
        o.v = 0;
        return *this;
    }

    [[nodiscard]] auto operator<=>(const move_only_value<N>&) const = default;

private:
    int v;
};

constexpr auto operator ""_mov0(unsigned long long v){
    return move_only_value<0>{static_cast<int>(v)};
}

constexpr auto operator ""_mov1(unsigned long long v){
    return move_only_value<1>{static_cast<int>(v)};
}

constexpr auto operator ""_mov2(unsigned long long v){
    return move_only_value<2>{static_cast<int>(v)};
}

constexpr auto operator ""_mov3(unsigned long long v){
    return move_only_value<3>{static_cast<int>(v)};
}
