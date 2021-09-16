#include <bitmap/bitmap.hpp>

#include <gtest/gtest.h>


TEST(BitmapTest, DefaultConstruction) {
    bmp::bitmap<int> image;

    EXPECT_EQ(image.width(), 0);
    EXPECT_EQ(image.height(), 0);
}

TEST(BitmapTest, WidthHeightConstruction) {
    bmp::bitmap<int> image(4, 5);

    EXPECT_EQ(image.width(), 4);
    EXPECT_EQ(image.height(), 5);
}

TEST(BitmapTest, SizeConstruction) {
    bmp::bitmap<int> image(bmp::size<std::size_t>(4, 5));

    EXPECT_EQ(image.width(), 4);
    EXPECT_EQ(image.height(), 5);
}

TEST(BitmapTest, CapacityAs) {
    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(127, 1));

        EXPECT_EQ(image.width_as<std::int8_t>(), 127);
        EXPECT_EQ(image.height_as<std::int8_t>(), 1);
        EXPECT_EQ(image.point_count_as<std::int8_t>(), 127);
        EXPECT_EQ(image.size_as<std::int8_t>(), (bmp::size<std::int8_t>(127, 1)));
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(1, 127));

        EXPECT_EQ(image.width_as<std::int8_t>(), 1);
        EXPECT_EQ(image.height_as<std::int8_t>(), 127);
        EXPECT_EQ(image.point_count_as<std::int8_t>(), 127);
        EXPECT_EQ(image.size_as<std::int8_t>(), (bmp::size<std::int8_t>(1, 127)));
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(128, 1));

        EXPECT_THROW(image.width_as<std::int8_t>(), std::runtime_error);
        EXPECT_EQ(image.height_as<std::int8_t>(), 1);
        EXPECT_THROW(image.point_count_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.size_as<std::int8_t>(), std::runtime_error);
    }

    {
        bmp::bitmap<int> image(bmp::size<std::size_t>(1, 128));

        EXPECT_EQ(image.width_as<std::int8_t>(), 1);
        EXPECT_THROW(image.height_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.point_count_as<std::int8_t>(), std::runtime_error);
        EXPECT_THROW(image.size_as<std::int8_t>(), std::runtime_error);
    }
}
