#include <bitmap/size.hpp>

#include <gtest/gtest.h>

#include "typed_value.hpp"


TEST(SizeTest, DefaultConstructionInt) {
    bmp::size<int> s;

    EXPECT_EQ(s.w(), 0);
    EXPECT_EQ(s.h(), 0);
}

TEST(SizeTest, DefaultConstruction) {
    bmp::size<typed_value<0>, typed_value<1>> s;

    EXPECT_EQ(s.w(), 0_tv0);
    EXPECT_EQ(s.h(), 0_tv1);
}

TEST(SizeTest, WHConstruction) {
    bmp::size s(4_tv0, 5_tv1);

    EXPECT_EQ(s.w(), 4_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}


TEST(SizeTest, CopyConstruction) {
    bmp::size s1(4_tv0, 5_tv1);
    bmp::size s2 = s1;

    EXPECT_EQ(s1.w(), 4_tv0);
    EXPECT_EQ(s1.h(), 5_tv1);
    EXPECT_EQ(s2.w(), 4_tv0);
    EXPECT_EQ(s2.h(), 5_tv1);
}


TEST(SizeTest, CopyAssign) {
    bmp::size s1(4_tv0, 5_tv1);
    bmp::size<typed_value<0>, typed_value<1>> s2;
    s2 = s1;

    EXPECT_EQ(s1.w(), 4_tv0);
    EXPECT_EQ(s1.h(), 5_tv1);
    EXPECT_EQ(s2.w(), 4_tv0);
    EXPECT_EQ(s2.h(), 5_tv1);
}


TEST(SizeTest, SetMove) {
    bmp::size<typed_value<0>, typed_value<1>> s;
    s.set(4_tv0, 5_tv1);

    EXPECT_EQ(s.w(), 4_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}

TEST(SizeTest, IsPositive) {
    EXPECT_TRUE( bmp::size( 4u,  5u).is_positive());
    EXPECT_TRUE( bmp::size( 4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::size(-4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::size( 4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::size(-4 , -5 ).is_positive());
}

TEST(SizeTest, Area) {
    EXPECT_EQ(bmp::size( 4u,  5u).area(), 20u);
    EXPECT_EQ(bmp::size( 4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::size(-4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::size( 4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::size(-4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::size(-4,   5u).area(), 20u);
    EXPECT_EQ(bmp::size( 4u, -5 ).area(), 20u);
}

TEST(SizeTest, Compare){
    EXPECT_EQ(bmp::size(4, 5), bmp::size(4, 5));
    EXPECT_NE(bmp::size(4, 5), bmp::size(2, 5));
    EXPECT_NE(bmp::size(4, 5), bmp::size(4, 3));

    EXPECT_EQ(bmp::size(4_tv0, 5_tv1), bmp::size(4_tv0, 5_tv1));
    EXPECT_NE(bmp::size(4_tv0, 5_tv1), bmp::size(2_tv0, 5_tv1));
    EXPECT_NE(bmp::size(4_tv0, 5_tv1), bmp::size(4_tv0, 3_tv1));
}

#include <bitmap/point.hpp>

TEST(SizeTest, ToPointTyped) {
    bmp::size s(4_tv0, 5_tv1);

    EXPECT_EQ(bmp::to_point(s), bmp::point(4_tv0, 5_tv1));
}

TEST(SizeTest, ToPointConvert) {
    bmp::size s(4.4, 5.6);

    EXPECT_EQ(bmp::to_point<double>(s), bmp::point(4.4, 5.6));
    EXPECT_EQ(bmp::to_point<int>(s), bmp::point(4, 5));
    EXPECT_EQ((bmp::to_point<int, double>(s)), bmp::point(4, 5.6));
    EXPECT_EQ((bmp::to_point<double, int>(s)), bmp::point(4.4, 5));
}
