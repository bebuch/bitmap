#pragma once

#include "matrix3x3.hpp"

#include <io_tools/io_c_array.hpp>

#include <ostream>


namespace bmp{


    template < typename charT, typename traits, typename T >
    std::basic_ostream< charT, traits >& operator<<(
        std::basic_ostream< charT, traits >& os,
        matrix3x3< T > const& m
    ){
        using ::io_tools::io_c_array::operator<<;
        return os << m.d;
    }


}
