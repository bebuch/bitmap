#pragma once

#include "size_io.hpp"
#include "point_io.hpp"
#include "rect.hpp"


namespace bmp{


    template < typename CharT, typename Traits,
        typename XT, typename WT, typename YT, typename HT >
    std::basic_ostream< CharT, Traits >& operator<<(
        std::basic_ostream< CharT, Traits >& os,
        rect< XT, WT, YT, HT > const& data
    ){
        return os << data.top_left() << ":" << data.size();
    }


}
