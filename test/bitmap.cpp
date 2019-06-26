#include <bitmap/bitmap.hpp>

#include <gtest/gtest.h>


TEST(BitmapTest, DefaultConstruction){
	bmp::bitmap< int > image;

	EXPECT_EQ(image.width(), 0);
	EXPECT_EQ(image.height(), 0);
}

TEST(BitmapTest, WidthHeightConstruction){
	bmp::bitmap< int > image(4, 5);

	EXPECT_EQ(image.width(), 4);
	EXPECT_EQ(image.height(), 5);
}
