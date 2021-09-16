#pragma once

#include "point.hpp"

#include <io_tools/expect.hpp>
#include <io_tools/input_wrapper.hpp>


namespace bmp{


    template < typename CharT, typename Traits, typename XT, typename YT >
    std::basic_ostream< CharT, Traits >& operator<<(
        std::basic_ostream< CharT, Traits >& os,
        point< XT, YT > const& data
    ){
        return os << data.x() << "x" << data.y();
    }


    template < typename CharT, typename Traits, typename XT, typename YT >
    std::basic_istream< CharT, Traits >& operator>>(
        std::basic_istream< CharT, Traits >& is,
        point< XT, YT >& data
    ){
        point< XT, YT > tmp;
        is >> io_tools::input_wrapper(tmp.x());
        if(!io_tools::expect(is, 'x')) return is;
        is >> io_tools::input_wrapper(tmp.y());

        if(is){
            data = std::move(tmp);
        }

        return is;
    }


}
