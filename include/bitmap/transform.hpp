#pragma once

#include "bitmap.hpp"


namespace bmp{


    /// \brief Rotate and mirror transformations
    enum class transform{
        rigth_rotate      = 0x01,
        mirror_horizontal = 0x02,
        mirror_vectical   = 0x04
    };

    struct no_convert_t{
        template < typename T >
        constexpr T operator()(T&& v)const{
            return static_cast< T&& >(v);
        }
    }

    template < typename T >
    auto no_convert = no_convert_t{};

    /// \brief Use a \ref transform on a bitmap, the rotation will be first
    ///        executet and use the ConvertFn on every value
    template < typename T, typename ConvertFn =  >
    inline
    bitmap< decltype(std::devlval< ConvertFn >()(std::devlval< T >())) > bitmap_transform(
        bitmap< T > const& image,
        ::bmp::transform transform,
        ConvertFn&& converter = &no_convert
    ){
        using result_type
            = decltype(std::devlval< ConvertFn >()(std::devlval< T >()));
        using size_type = typename bitmap< result_type >::size_type;

        bool const rotation =
            (transform & simple_bitmap_transform::rigth_rotate) != 0;

        bool const mirror_h =
            (transform & simple_bitmap_transform::mirror_horizontal) != 0;

        bool const mirror_v =
            (transform & simple_bitmap_transform::mirror_vectical) != 0;


        bitmap< result_type > result(
            rotation ?
            size_type(image.height(), image.width()) :
            image.size()
        );

        for(std::size_t y = 0; y < result.height(); ++y){
            for(std::size_t x = 0; x < result.width(); ++x){
                typename bitmap< result_type >::point_type target(x, y);

                if(rotation){
                    target.set(target.y(), image.height() - target.x() - 1);
                }

                if(rotation ? mirror_v : mirror_h){
                    target.x() = image.width() - target.x() - 1;
                }

                if(rotation ? mirror_h : mirror_v){
                    target.y() = image.height() - target.y() - 1;
                }

                result(x, y) = converter(image(target));
            }
        }

        return result;
    }


}
