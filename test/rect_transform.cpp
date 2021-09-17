#include <bitmap/matrix3x3_io.hpp>
#include <bitmap/rect_io.hpp>
#include <bitmap/rect_transform.hpp>

#include <io_tools/io_std_array.hpp>

#include <gtest/gtest.h>

#include <array>


constexpr std::array<bmp::point<double>, 4> from{{{84, 93}, {166, 100}, {90, 210}, {163, 200}}};
constexpr std::array<bmp::point<double>, 4> to{{{10, 10}, {20, 10}, {10, 20}, {20, 20}}};

constexpr std::array<bmp::point<double>, 4> ref_contour{
    {{3.36015, 4.72586}, {43.0205, -2.22179}, {-0.133652, 26.8196}, {60.2168, 43.8053}}};


bool nearly_eq(bmp::point<double> const& p1, bmp::point<double> const& p2) {
    return std::abs(p1.x() - p2.x()) < 0.001 && std::abs(p1.y() - p2.y()) < 0.001;
}

bool nearly_eq(
    std::array<bmp::point<double>, 4> const& l1,
    std::array<bmp::point<double>, 4> const& l2) {
    for(std::size_t i = 0; i < 4; ++i) {
        if(!nearly_eq(l1[i], l2[i])) {
            return false;
        }
    }
    return true;
}

TEST(RectTransformTest, TransformPoint) {
    auto const c = bmp::rect_transform_homography(from, to);
    EXPECT_TRUE(nearly_eq(to[0], transform_point(c, from[0])));
    EXPECT_TRUE(nearly_eq(to[1], transform_point(c, from[1])));
    EXPECT_TRUE(nearly_eq(to[2], transform_point(c, from[2])));
    EXPECT_TRUE(nearly_eq(to[3], transform_point(c, from[3])));
}

TEST(RectTransformTest, ImageContour) {
    auto const c = bmp::rect_transform_homography(from, to);

    auto const image_size = bmp::size<std::size_t>{300, 300};
    auto const contour = transform_image_contour(c, image_size);
    EXPECT_TRUE(nearly_eq(contour, ref_contour));

    auto ic = bmp::image_contour(contour);
    EXPECT_EQ(ic, (bmp::rect<long, std::size_t>(-1, 62, -3, 47)));

    bmp::bitmap<std::uint8_t> source(image_size);

    auto const target = transform_bitmap(invert(c), source, ic);
    EXPECT_EQ(target.size(), (bmp::size<std::size_t>(62, 47)));

    auto const target_d = bmp::transform_bitmap<double>(invert(c), source, ic);
    EXPECT_EQ(target_d.size(), (bmp::size<std::size_t>(62, 47)));
}
