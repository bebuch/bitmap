#include <bitmap/bitmap_io.hpp>

#include <gtest/gtest.h>


TEST(BitmapIOTest, Output) {
    std::ostringstream os;
    os << bmp::bitmap<int>({{1, 2, 3}, {4, 5, 6}});
    EXPECT_EQ(os.str(), "[3x2]{{1, 2, 3}, {4, 5, 6}}");
}
