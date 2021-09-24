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


TEST(SizeTest, TypeCast) {
    EXPECT_EQ(static_cast<bmp::size<int>>(bmp::size(3.3, 4.4)), bmp::size(3, 4));
    EXPECT_EQ((static_cast<bmp::size<int, unsigned>>(bmp::size(3.3, 4.4))), bmp::size(3, 4u));
}


#include <bitmap/point.hpp>

TEST(SizeTest, ToPointConvert) {
    EXPECT_EQ(to_point(bmp::size(4_tv0, 5_tv1)), bmp::point(4_tv0, 5_tv1));
}

TEST(SizeTest, Contains) {
    EXPECT_TRUE(contains(bmp::size(4_tv0, 5_tv1), bmp::point(3_tv0, 4_tv1)));
    EXPECT_FALSE(contains(bmp::size(4_tv0, 5_tv1), bmp::point(3_tv0, 5_tv1)));
    EXPECT_FALSE(contains(bmp::size(4_tv0, 5_tv1), bmp::point(4_tv0, 4_tv1)));

    EXPECT_TRUE(contains(bmp::size(-4_tv0, -5_tv1), bmp::point(-5_tv0, -6_tv1)));
    EXPECT_FALSE(contains(bmp::size(-4_tv0, -5_tv1), bmp::point(-5_tv0, -5_tv1)));
    EXPECT_FALSE(contains(bmp::size(-4_tv0, -5_tv1), bmp::point(-4_tv0, -6_tv1)));
}
