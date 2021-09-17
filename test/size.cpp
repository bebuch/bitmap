#include <bitmap/size.hpp>

#include <gtest/gtest.h>

#include "move_only_value.hpp"


TEST(SizeTest, DefaultConstruction) {
    bmp::size<int> s;

    EXPECT_EQ(s.width(), 0);
    EXPECT_EQ(s.height(), 0);
}

TEST(SizeTest, WidthHeightConstruction) {
    bmp::size s(4, 5);

    EXPECT_EQ(s.width(), 4);
    EXPECT_EQ(s.height(), 5);
}

TEST(SizeTest, CopyConstruction) {
    bmp::size s1(4, 5);
    bmp::size s2(s1);

    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveConstruction) {
    bmp::size s1(4, 5);
    bmp::size s2(std::move(s1));

    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveConstructionMoveOnly) {
    bmp::size s1(4_mov0, 5_mov1);
    bmp::size s2(std::move(s1));

    EXPECT_EQ(s1.width(), 0_mov0);
    EXPECT_EQ(s1.height(), 0_mov1);
    EXPECT_EQ(s2.width(), 4_mov0);
    EXPECT_EQ(s2.height(), 5_mov1);
}

TEST(SizeTest, CopyAssign) {
    bmp::size s1(4, 5);
    bmp::size<int> s2;
    s2 = s1;

    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveAssign) {
    bmp::size s1(4_mov0, 5_mov1);
    bmp::size<move_only_value<0>, move_only_value<1>> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.width(), 0_mov0);
    EXPECT_EQ(s1.height(), 0_mov1);
    EXPECT_EQ(s2.width(), 4_mov0);
    EXPECT_EQ(s2.height(), 5_mov1);
}

TEST(SizeTest, MoveAssignMoveOnly) {
    bmp::size s1(4_mov0, 5_mov1);
    bmp::size<move_only_value<0>, move_only_value<1>> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.width(), 0_mov0);
    EXPECT_EQ(s1.height(), 0_mov1);
    EXPECT_EQ(s2.width(), 4_mov0);
    EXPECT_EQ(s2.height(), 5_mov1);
}

TEST(SizeTest, Set) {
    bmp::size<int> s;
    s.set(4, 5);

    EXPECT_EQ(s.width(), 4);
    EXPECT_EQ(s.height(), 5);
}

TEST(SizeTest, SetMoveOnly) {
    bmp::size<move_only_value<0>, move_only_value<1>> s;
    s.set(4_mov0, 5_mov1);

    EXPECT_EQ(s.width(), 4_mov0);
    EXPECT_EQ(s.height(), 5_mov1);
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

    EXPECT_EQ(bmp::size(4, 5.2f), bmp::size(4, 5.2f));
    EXPECT_NE(bmp::size(4, 5.2f), bmp::size(2, 5.2f));
    EXPECT_NE(bmp::size(4, 5.2f), bmp::size(4, 3.2f));
}
