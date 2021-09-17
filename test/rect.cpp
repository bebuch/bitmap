#include <bitmap/rect.hpp>

#include <gtest/gtest.h>

#include "move_only_value.hpp"
#include "typed_value.hpp"


TEST(RectTest, DefaultConstruction) {
    bmp::rect<int> s;

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
    EXPECT_EQ(s.w(), 0);
    EXPECT_EQ(s.h(), 0);
}

TEST(RectTest, DefaultConstructionMoveOnly) {
    bmp::rect<move_only_value<0>, move_only_value<2>, move_only_value<1>, move_only_value<3>> s;

    EXPECT_EQ(s.x(), 0_mov0);
    EXPECT_EQ(s.y(), 0_mov1);
    EXPECT_EQ(s.w(), 0_mov2);
    EXPECT_EQ(s.h(), 0_mov3);
}

TEST(RectTest, XYWHConstruction) {
    bmp::rect s(2, 4, 3, 5);

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, XYWHConstructionMoveOnly) {
    bmp::rect s(2_mov0, 4_mov2, 3_mov1, 5_mov3);

    EXPECT_EQ(s.x(), 2_mov0);
    EXPECT_EQ(s.y(), 3_mov1);
    EXPECT_EQ(s.w(), 4_mov2);
    EXPECT_EQ(s.h(), 5_mov3);
}

TEST(RectTest, PSConstruction) {
    bmp::rect s(bmp::point(2, 3), bmp::size(4, 5));

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, PSConstructionMoveOnly) {
    bmp::rect s(bmp::point(2_mov0, 3_mov1), bmp::size(4_mov2, 5_mov3));

    EXPECT_EQ(s.x(), 2_mov0);
    EXPECT_EQ(s.y(), 3_mov1);
    EXPECT_EQ(s.w(), 4_mov2);
    EXPECT_EQ(s.h(), 5_mov3);
}

TEST(RectTest, WHConstruction) {
    bmp::rect s(4, 5);

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, WHConstructionMoveOnly) {
    bmp::rect s(4_mov0, 5_mov1);

    EXPECT_EQ(s.x(), 0_mov0);
    EXPECT_EQ(s.y(), 0_mov1);
    EXPECT_EQ(s.w(), 4_mov0);
    EXPECT_EQ(s.h(), 5_mov1);
}

TEST(RectTest, SConstruction) {
    bmp::rect s(bmp::size(4, 5));

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, SConstructionMoveOnly) {
    bmp::rect s(bmp::size(4_mov0, 5_mov1));

    EXPECT_EQ(s.x(), 0_mov0);
    EXPECT_EQ(s.y(), 0_mov1);
    EXPECT_EQ(s.w(), 4_mov0);
    EXPECT_EQ(s.h(), 5_mov1);
}

TEST(RectTest, PConstruction) {
    bmp::rect s(bmp::point(2, 7));

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
    EXPECT_EQ(s.w(), 3);
    EXPECT_EQ(s.h(), 8);
}

TEST(RectTest, PConstructionTyped) {
    bmp::rect s(bmp::point(2_tv0, 7_tv1));

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv1);
    EXPECT_EQ(s.w(), 3_tv0);
    EXPECT_EQ(s.h(), 8_tv1);
}

TEST(RectTest, PPConstruction) {
    bmp::rect s(bmp::point(2, 3), bmp::point(8, 7));

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.w(), 7);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, PPConstructionTyped) {
    bmp::rect s(bmp::point(2_tv0, 3_tv1), bmp::point(8_tv0, 7_tv1));

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 7_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}

TEST(RectTest, CopyConstruction) {
    bmp::rect s1(2, 4, 3, 5);
    bmp::rect s2(s1);

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.w(), 4);
    EXPECT_EQ(s1.h(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.w(), 4);
    EXPECT_EQ(s2.h(), 5);
}

TEST(RectTest, MoveConstruction) {
    bmp::rect s1(2, 4, 3, 5);
    bmp::rect s2(std::move(s1));

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.w(), 4);
    EXPECT_EQ(s1.h(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.w(), 4);
    EXPECT_EQ(s2.h(), 5);
}

TEST(RectTest, MoveConstructionMoveOnly) {
    bmp::rect s1(2_mov0, 4_mov2, 3_mov1, 5_mov3);
    bmp::rect s2(std::move(s1));

    EXPECT_EQ(s1.x(), 0_mov0);
    EXPECT_EQ(s1.y(), 0_mov1);
    EXPECT_EQ(s1.w(), 0_mov2);
    EXPECT_EQ(s1.h(), 0_mov3);
    EXPECT_EQ(s2.x(), 2_mov0);
    EXPECT_EQ(s2.y(), 3_mov1);
    EXPECT_EQ(s2.w(), 4_mov2);
    EXPECT_EQ(s2.h(), 5_mov3);
}

TEST(RectTest, CopyAssign) {
    bmp::rect s1(2, 4, 3, 5);
    bmp::rect<int> s2;
    s2 = s1;

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.w(), 4);
    EXPECT_EQ(s1.h(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.w(), 4);
    EXPECT_EQ(s2.h(), 5);
}

TEST(RectTest, MoveAssign) {
    bmp::rect s1(2, 4, 3, 5);
    bmp::rect<int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.w(), 4);
    EXPECT_EQ(s1.h(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.w(), 4);
    EXPECT_EQ(s2.h(), 5);
}

TEST(RectTest, MoveAssignMoveOnly) {
    bmp::rect s1(2_mov0, 4_mov2, 3_mov1, 5_mov3);
    bmp::rect<move_only_value<0>, move_only_value<2>, move_only_value<1>, move_only_value<3>> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x(), 0_mov0);
    EXPECT_EQ(s1.y(), 0_mov1);
    EXPECT_EQ(s1.w(), 0_mov2);
    EXPECT_EQ(s1.h(), 0_mov3);
    EXPECT_EQ(s2.x(), 2_mov0);
    EXPECT_EQ(s2.y(), 3_mov1);
    EXPECT_EQ(s2.w(), 4_mov2);
    EXPECT_EQ(s2.h(), 5_mov3);
}

TEST(RectTest, Set) {
    bmp::rect<int> s;
    s.set(2, 4, 3, 5);

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, SetMoveOnly) {
    bmp::rect<move_only_value<0>, move_only_value<2>, move_only_value<1>, move_only_value<3>> s;
    s.set(2_mov0, 4_mov2, 3_mov1, 5_mov3);

    EXPECT_EQ(s.x(), 2_mov0);
    EXPECT_EQ(s.y(), 3_mov1);
    EXPECT_EQ(s.w(), 4_mov2);
    EXPECT_EQ(s.h(), 5_mov3);
}

TEST(RectTest, SetXYWH) {
    bmp::rect<int> s;
    s.set_x(2);
    s.set_y(3);
    s.set_w(4);
    s.set_h(5);

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.w(), 4);
    EXPECT_EQ(s.h(), 5);
}

TEST(RectTest, SetXYWHMoveOnly) {
    bmp::rect<move_only_value<0>, move_only_value<2>, move_only_value<1>, move_only_value<3>> s;
    s.set_x(2_mov0);
    s.set_y(3_mov1);
    s.set_w(4_mov2);
    s.set_h(5_mov3);

    EXPECT_EQ(s.x(), 2_mov0);
    EXPECT_EQ(s.y(), 3_mov1);
    EXPECT_EQ(s.w(), 4_mov2);
    EXPECT_EQ(s.h(), 5_mov3);
}

TEST(RectTest, SetLTRBTyped) {
    bmp::rect s(12_tv0, 21_tv0, 16_tv1, 28_tv1);

    EXPECT_EQ(s.x(), 12_tv0);
    EXPECT_EQ(s.y(), 16_tv1);
    EXPECT_EQ(s.w(), 21_tv0);
    EXPECT_EQ(s.h(), 28_tv1);

    EXPECT_EQ(s.pos(),  bmp::point(12_tv0, 16_tv1));
    EXPECT_EQ(s.size(), bmp::size(21_tv0, 28_tv1));

    EXPECT_EQ(s.l(), 12_tv0);
    EXPECT_EQ(s.t(), 16_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    EXPECT_EQ(s.lt(), bmp::point(12_tv0, 16_tv1));
    EXPECT_EQ(s.rt(), bmp::point(32_tv0, 16_tv1));
    EXPECT_EQ(s.lb(), bmp::point(12_tv0, 43_tv1));
    EXPECT_EQ(s.rb(), bmp::point(32_tv0, 43_tv1));

    s.set_l(10_tv0);

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 16_tv1);
    EXPECT_EQ(s.w(), 23_tv0);
    EXPECT_EQ(s.h(), 28_tv1);

    EXPECT_EQ(s.pos(),  bmp::point(10_tv0, 16_tv1));
    EXPECT_EQ(s.size(), bmp::size(23_tv0, 28_tv1));

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 16_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    EXPECT_EQ(s.lt(), bmp::point(10_tv0, 16_tv1));
    EXPECT_EQ(s.rt(), bmp::point(32_tv0, 16_tv1));
    EXPECT_EQ(s.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(s.rb(), bmp::point(32_tv0, 43_tv1));

    s.set_t(20_tv1);

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 20_tv1);
    EXPECT_EQ(s.w(), 23_tv0);
    EXPECT_EQ(s.h(), 24_tv1);

    EXPECT_EQ(s.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.size(), bmp::size(23_tv0, 24_tv1));

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 20_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    EXPECT_EQ(s.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.rt(), bmp::point(32_tv0, 20_tv1));
    EXPECT_EQ(s.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(s.rb(), bmp::point(32_tv0, 43_tv1));

    s.set_r(35_tv0);

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 20_tv1);
    EXPECT_EQ(s.w(), 26_tv0);
    EXPECT_EQ(s.h(), 24_tv1);

    EXPECT_EQ(s.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.size(), bmp::size(26_tv0, 24_tv1));

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 20_tv1);
    EXPECT_EQ(s.r(), 35_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    EXPECT_EQ(s.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.rt(), bmp::point(35_tv0, 20_tv1));
    EXPECT_EQ(s.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(s.rb(), bmp::point(35_tv0, 43_tv1));

    s.set_b(57_tv1);

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 20_tv1);
    EXPECT_EQ(s.w(), 26_tv0);
    EXPECT_EQ(s.h(), 38_tv1);

    EXPECT_EQ(s.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.size(), bmp::size(26_tv0, 38_tv1));

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 20_tv1);
    EXPECT_EQ(s.r(), 35_tv0);
    EXPECT_EQ(s.b(), 57_tv1);

    EXPECT_EQ(s.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(s.rt(), bmp::point(35_tv0, 20_tv1));
    EXPECT_EQ(s.lb(), bmp::point(10_tv0, 57_tv1));
    EXPECT_EQ(s.rb(), bmp::point(35_tv0, 57_tv1));
}

TEST(RectTest, SetLTRBPointsTyped) {
    bmp::rect s(12_tv0, 21_tv0, 16_tv1, 28_tv1);

    EXPECT_EQ(s.x(), 12_tv0);
    EXPECT_EQ(s.y(), 16_tv1);
    EXPECT_EQ(s.w(), 21_tv0);
    EXPECT_EQ(s.h(), 28_tv1);

    EXPECT_EQ(s.l(), 12_tv0);
    EXPECT_EQ(s.t(), 16_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    s.set_lt(bmp::point(10_tv0, 20_tv1));

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 20_tv1);
    EXPECT_EQ(s.w(), 23_tv0);
    EXPECT_EQ(s.h(), 24_tv1);

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 20_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);

    s.set_rb(bmp::point(35_tv0, 57_tv1));

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 20_tv1);
    EXPECT_EQ(s.w(), 26_tv0);
    EXPECT_EQ(s.h(), 38_tv1);

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 20_tv1);
    EXPECT_EQ(s.r(), 35_tv0);
    EXPECT_EQ(s.b(), 57_tv1);

    s.set_rt(bmp::point(32_tv0, 16_tv1));

    EXPECT_EQ(s.x(), 10_tv0);
    EXPECT_EQ(s.y(), 16_tv1);
    EXPECT_EQ(s.w(), 23_tv0);
    EXPECT_EQ(s.h(), 42_tv1);

    EXPECT_EQ(s.l(), 10_tv0);
    EXPECT_EQ(s.t(), 16_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 57_tv1);

    s.set_lb(bmp::point(12_tv0, 43_tv1));

    EXPECT_EQ(s.x(), 12_tv0);
    EXPECT_EQ(s.y(), 16_tv1);
    EXPECT_EQ(s.w(), 21_tv0);
    EXPECT_EQ(s.h(), 28_tv1);

    EXPECT_EQ(s.l(), 12_tv0);
    EXPECT_EQ(s.t(), 16_tv1);
    EXPECT_EQ(s.r(), 32_tv0);
    EXPECT_EQ(s.b(), 43_tv1);
}

TEST(RectTest, IsPositive) {
    EXPECT_TRUE( bmp::rect(2,  4u, 3,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(2,  4 , 3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -4 , 3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2,  4 , 3, -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -4 , 3, -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(2,  4u, -3,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(2,  4 , -3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -4 , -3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2,  4 , -3, -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -4 , -3, -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(-2,  4u, 3,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(-2,  4 , 3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -4 , 3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2,  4 , 3, -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -4 , 3, -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(-2,  4u, -3,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(-2,  4 , -3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -4 , -3,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2,  4 , -3, -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -4 , -3, -5 ).is_positive());
}

TEST(RectTest, Area) {
    EXPECT_EQ(bmp::rect(2,  4u, 3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4,  3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4,  3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4u, 3, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(-2,  4u, 3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4,  3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4,  3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4u, 3, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(2,  4u, -3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4,  -3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  -3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4,  -3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  -3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -4,  -3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2,  4u, -3, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(-2,  4u, -3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4,  -3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  -3,  5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4,  -3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  -3, -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -4,  -3,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2,  4u, -3, -5 ).area(), 20u);
}

TEST(RectTest, Compare){
    EXPECT_EQ(bmp::rect(2, 3, 4, 5), bmp::rect(2, 3, 4, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 2, 3, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 4, 3, 3));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(5, 4, 3, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 4, 4, 5));

    EXPECT_EQ(bmp::rect(2.1, 4, 3u, 5.2f), bmp::rect(2.1, 4, 3u, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 4, 3u, 5.2f), bmp::rect(2.1, 2, 3u, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 4, 3u, 5.2f), bmp::rect(2.1, 4, 3u, 3.2f));
    EXPECT_NE(bmp::rect(2.1, 4, 3u, 5.2f), bmp::rect(2.1, 4, 4u, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 4, 3u, 5.2f), bmp::rect(2.2, 4, 3u, 5.2f));
}
