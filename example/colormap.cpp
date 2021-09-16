#include <bitmap/bitmap.hpp>
#include <bitmap/colormap.hpp>
#include <bitmap/binary_write.hpp>

#include <iostream>
#include <iomanip>


int main(){
    int bits = 8;
    auto colormap = bmp::colormap::make_uniform({
        {0   , 0   , 0   , 0   , 1   , 1   , 0.75, 1   },
        {0   , 0   , 1   , 0.5 , 1   , 0   , 0   , 1   },
        {0   , 1   , 1   , 0   , 0   , 0   , 1   , 1   }}, bits);

    for(auto v: colormap){
        std::cout
            << std::setw(10) << static_cast< double >(v.r) << " "
            << std::setw(10) << static_cast< double >(v.g) << " "
            << std::setw(10) << static_cast< double >(v.b) << "\n";
    }

    bmp::bitmap< bmp::pixel::rgb8u > colorbar(std::pow(2, bits), 10);

    for(std::size_t x = 0; x < colorbar.width(); ++x){
        for(std::size_t y = 0; y < colorbar.height(); ++y){
            colorbar(x, y) = colormap[x];
        }
    }

    bmp::binary_write(colorbar, "colorbar.bbf");
}
