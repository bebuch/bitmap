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

TEST(BitmapTest, ArrayConstruction) {
    bmp::bitmap<int> image({{1, 2, 3}, {4, 5, 6}});

    ASSERT_EQ(image.w(), 3);
    ASSERT_EQ(image.h(), 2);
    EXPECT_EQ(image(0, 0), 1);
    EXPECT_EQ(image(1, 0), 2);
    EXPECT_EQ(image(2, 0), 3);
    EXPECT_EQ(image(0, 1), 4);
    EXPECT_EQ(image(1, 1), 5);
    EXPECT_EQ(image(2, 1), 6);
}

TEST(BitmapTest, clear) {
    bmp::bitmap<int> image({{1, 2, 3}, {4, 5, 6}});

    image.clear();

    ASSERT_EQ(image.w(), 0);
    ASSERT_EQ(image.h(), 0);
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
