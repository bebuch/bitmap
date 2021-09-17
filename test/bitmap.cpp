#include <bitmap/bitmap.hpp>

#include <gtest/gtest.h>


TEST(BitmapTest, DefaultConstruction) {
    bmp::bitmap<int> image;

    EXPECT_EQ(image.w(), 0);
    EXPECT_EQ(image.h(), 0);
}

TEST(BitmapTest, WidthHeightConstruction) {
    bmp::bitmap<int> image(4, 5);

    EXPECT_EQ(image.w(), 4);
    EXPECT_EQ(image.h(), 5);
}

TEST(BitmapTest, SizeConstruction) {
    bmp::bitmap<int> image(bmp::size<std::size_t>(4, 5));

    EXPECT_EQ(image.w(), 4);
    EXPECT_EQ(image.h(), 5);
}

TEST(BitmapTest, CapacityAs) {
    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(127, 1));

        EXPECT_EQ(image.w_as<std::int8_t>(), 127);
        EXPECT_EQ(image.h_as<std::int8_t>(), 1);
        EXPECT_EQ(image.point_count_as<std::int8_t>(), 127);
        EXPECT_EQ(image.size_as<std::int8_t>(), (bmp::size<std::int8_t>(127, 1)));
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(1, 127));

        EXPECT_EQ(image.w_as<std::int8_t>(), 1);
        EXPECT_EQ(image.h_as<std::int8_t>(), 127);
        EXPECT_EQ(image.point_count_as<std::int8_t>(), 127);
        EXPECT_EQ(image.size_as<std::int8_t>(), (bmp::size<std::int8_t>(1, 127)));
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(128, 1));

        EXPECT_THROW(image.w_as<std::int8_t>(), std::runtime_error);
        EXPECT_EQ(image.h_as<std::int8_t>(), 1);
        EXPECT_THROW(image.point_count_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.size_as<std::int8_t>(), std::runtime_error);
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(1, 128));

        EXPECT_EQ(image.w_as<std::int8_t>(), 1);
        EXPECT_THROW(image.h_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.point_count_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.size_as<std::int8_t>(), std::runtime_error);
    }
}
