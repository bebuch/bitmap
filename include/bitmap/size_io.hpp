#pragma once

#include "size.hpp"

#include <io_tools/expect.hpp>
#include <io_tools/input_wrapper.hpp>


namespace bmp {


    template <typename CharT, typename Traits, typename WT, typename HT>
    std::basic_ostream<CharT, Traits>&
        operator<<(std::basic_ostream<CharT, Traits>& os, size<WT, HT> const& data) {
        return os << data.w() << "x" << data.h();
    }


    template <typename CharT, typename Traits, typename WT, typename HT>
    std::basic_istream<CharT, Traits>&
        operator>>(std::basic_istream<CharT, Traits>& is, size<WT, HT>& data) {
        size<WT, HT> tmp;
        is >> io_tools::input_wrapper(tmp.w());
        if(!io_tools::expect(is, 'x'))
            return is;
        is >> io_tools::input_wrapper(tmp.h());

        if(is) {
            data = std::move(tmp);
        }

        return is;
    }


}
