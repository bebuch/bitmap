#include <bitmap/rect.hpp>

#include <gtest/gtest.h>

#include "typed_value.hpp"


TEST(RectTest, DefaultConstructionTyped1) {
    bmp::rect<typed_value<0>> s;

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv0);
    EXPECT_EQ(s.w(), 0_tv0);
    EXPECT_EQ(s.h(), 0_tv0);
}

TEST(RectTest, DefaultConstructionTyped2) {
    bmp::rect<typed_value<0>, typed_value<1>> s;

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv0);
    EXPECT_EQ(s.w(), 0_tv1);
    EXPECT_EQ(s.h(), 0_tv1);
}

TEST(RectTest, DefaultConstructionTyped3) {
    bmp::rect<typed_value<0>, typed_value<1>, typed_value<2>> s;

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv2);
    EXPECT_EQ(s.w(), 0_tv1);
    EXPECT_EQ(s.h(), 0_tv1);
}

TEST(RectTest, DefaultConstructionTyped4) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> s;

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv1);
    EXPECT_EQ(s.w(), 0_tv2);
    EXPECT_EQ(s.h(), 0_tv3);
}

TEST(RectTest, XYWHConstruction) {
    bmp::rect s(2_tv0, 4_tv2, 3_tv1, 5_tv3);

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 4_tv2);
    EXPECT_EQ(s.h(), 5_tv3);
}

TEST(RectTest, PSConstruction) {
    bmp::rect s(bmp::point(2_tv0, 3_tv1), bmp::size(4_tv2, 5_tv3));

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 4_tv2);
    EXPECT_EQ(s.h(), 5_tv3);
}

TEST(RectTest, WHConstruction) {
    bmp::rect s(4_tv0, 5_tv1);

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv1);
    EXPECT_EQ(s.w(), 4_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}

TEST(RectTest, SConstruction) {
    bmp::rect s(bmp::size(4_tv0, 5_tv1));

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv1);
    EXPECT_EQ(s.w(), 4_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}

TEST(RectTest, PConstruction) {
    bmp::rect s(bmp::point(2_tv0, 7_tv1));

    EXPECT_EQ(s.x(), 0_tv0);
    EXPECT_EQ(s.y(), 0_tv1);
    EXPECT_EQ(s.w(), 3_tv0);
    EXPECT_EQ(s.h(), 8_tv1);
}

TEST(RectTest, PPConstruction) {
    bmp::rect s(bmp::point(2_tv0, 3_tv1), bmp::point(8_tv0, 7_tv1));

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 7_tv0);
    EXPECT_EQ(s.h(), 5_tv1);
}

TEST(RectTest, CopyConstruction) {
    bmp::rect s1(2_tv0, 4_tv2, 3_tv1, 5_tv3);
    bmp::rect s2 = s1;

    EXPECT_EQ(s1.x(), 2_tv0);
    EXPECT_EQ(s1.y(), 3_tv1);
    EXPECT_EQ(s1.w(), 4_tv2);
    EXPECT_EQ(s1.h(), 5_tv3);
    EXPECT_EQ(s2.x(), 2_tv0);
    EXPECT_EQ(s2.y(), 3_tv1);
    EXPECT_EQ(s2.w(), 4_tv2);
    EXPECT_EQ(s2.h(), 5_tv3);
}

TEST(RectTest, CopyAssign) {
    bmp::rect s1(2_tv0, 4_tv2, 3_tv1, 5_tv3);
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> s2;
    s2 = s1;

    EXPECT_EQ(s1.x(), 2_tv0);
    EXPECT_EQ(s1.y(), 3_tv1);
    EXPECT_EQ(s1.w(), 4_tv2);
    EXPECT_EQ(s1.h(), 5_tv3);
    EXPECT_EQ(s2.x(), 2_tv0);
    EXPECT_EQ(s2.y(), 3_tv1);
    EXPECT_EQ(s2.w(), 4_tv2);
    EXPECT_EQ(s2.h(), 5_tv3);
}

TEST(RectTest, Set) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> s;
    s.set(2_tv0, 4_tv2, 3_tv1, 5_tv3);

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 4_tv2);
    EXPECT_EQ(s.h(), 5_tv3);
}

TEST(RectTest, SetXYWH) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> s;
    s.set_x(2_tv0);
    s.set_y(3_tv1);
    s.set_w(4_tv2);
    s.set_h(5_tv3);

    EXPECT_EQ(s.x(), 2_tv0);
    EXPECT_EQ(s.y(), 3_tv1);
    EXPECT_EQ(s.w(), 4_tv2);
    EXPECT_EQ(s.h(), 5_tv3);
}

TEST(RectTest, SetLTRB) {
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

TEST(RectTest, SetLTRBPoints) {
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
    EXPECT_EQ(bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3), bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3));
    EXPECT_NE(bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3), bmp::rect(2_tv0, 2_tv1, 3_tv2, 5_tv3));
    EXPECT_NE(bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3), bmp::rect(2_tv0, 4_tv1, 3_tv2, 3_tv3));
    EXPECT_NE(bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3), bmp::rect(5_tv0, 4_tv1, 3_tv2, 5_tv3));
    EXPECT_NE(bmp::rect(2_tv0, 3_tv1, 4_tv2, 5_tv3), bmp::rect(2_tv0, 4_tv1, 4_tv2, 5_tv3));
}
