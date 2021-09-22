#include <bitmap/rect.hpp>

#include <gtest/gtest.h>

#include "typed_value.hpp"


TEST(RectTest, DefaultConstructionTyped1) {
    bmp::rect<typed_value<0>> r;

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv0);
    EXPECT_EQ(r.w(), 0_tv0);
    EXPECT_EQ(r.h(), 0_tv0);
}

TEST(RectTest, DefaultConstructionTyped2) {
    bmp::rect<typed_value<0>, typed_value<1>> r;

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv0);
    EXPECT_EQ(r.w(), 0_tv1);
    EXPECT_EQ(r.h(), 0_tv1);
}

TEST(RectTest, DefaultConstructionTyped3) {
    bmp::rect<typed_value<0>, typed_value<1>, typed_value<2>> r;

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv2);
    EXPECT_EQ(r.w(), 0_tv1);
    EXPECT_EQ(r.h(), 0_tv1);
}

TEST(RectTest, DefaultConstructionTyped4) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> r;

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv1);
    EXPECT_EQ(r.w(), 0_tv2);
    EXPECT_EQ(r.h(), 0_tv3);
}

TEST(RectTest, XYWHConstruction) {
    bmp::rect r(2_tv0, 4_tv2, 3_tv1, 5_tv3);

    EXPECT_EQ(r.x(), 2_tv0);
    EXPECT_EQ(r.y(), 3_tv1);
    EXPECT_EQ(r.w(), 4_tv2);
    EXPECT_EQ(r.h(), 5_tv3);
}

TEST(RectTest, PSConstruction) {
    bmp::rect r(bmp::point(2_tv0, 3_tv1), bmp::size(4_tv2, 5_tv3));

    EXPECT_EQ(r.x(), 2_tv0);
    EXPECT_EQ(r.y(), 3_tv1);
    EXPECT_EQ(r.w(), 4_tv2);
    EXPECT_EQ(r.h(), 5_tv3);
}

TEST(RectTest, WHConstruction) {
    bmp::rect r(4_tv0, 5_tv1);

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv1);
    EXPECT_EQ(r.w(), 4_tv0);
    EXPECT_EQ(r.h(), 5_tv1);
}

TEST(RectTest, SConstruction) {
    bmp::rect r(bmp::size(4_tv0, 5_tv1));

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv1);
    EXPECT_EQ(r.w(), 4_tv0);
    EXPECT_EQ(r.h(), 5_tv1);
}

TEST(RectTest, PConstruction) {
    bmp::rect r(bmp::point(2_tv0, 7_tv1));

    EXPECT_EQ(r.x(), 0_tv0);
    EXPECT_EQ(r.y(), 0_tv1);
    EXPECT_EQ(r.w(), 3_tv0);
    EXPECT_EQ(r.h(), 8_tv1);
}

TEST(RectTest, PPConstruction) {
    bmp::rect r(bmp::point(2_tv0, 3_tv1), bmp::point(8_tv0, 7_tv1));

    EXPECT_EQ(r.x(), 2_tv0);
    EXPECT_EQ(r.y(), 3_tv1);
    EXPECT_EQ(r.w(), 7_tv0);
    EXPECT_EQ(r.h(), 5_tv1);
}

TEST(RectTest, CopyConstruction) {
    bmp::rect r1(2_tv0, 4_tv2, 3_tv1, 5_tv3);
    bmp::rect r2 = r1;

    EXPECT_EQ(r1.x(), 2_tv0);
    EXPECT_EQ(r1.y(), 3_tv1);
    EXPECT_EQ(r1.w(), 4_tv2);
    EXPECT_EQ(r1.h(), 5_tv3);
    EXPECT_EQ(r2.x(), 2_tv0);
    EXPECT_EQ(r2.y(), 3_tv1);
    EXPECT_EQ(r2.w(), 4_tv2);
    EXPECT_EQ(r2.h(), 5_tv3);
}

TEST(RectTest, CopyAssign) {
    bmp::rect r1(2_tv0, 4_tv2, 3_tv1, 5_tv3);
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> r2;
    r2 = r1;

    EXPECT_EQ(r1.x(), 2_tv0);
    EXPECT_EQ(r1.y(), 3_tv1);
    EXPECT_EQ(r1.w(), 4_tv2);
    EXPECT_EQ(r1.h(), 5_tv3);
    EXPECT_EQ(r2.x(), 2_tv0);
    EXPECT_EQ(r2.y(), 3_tv1);
    EXPECT_EQ(r2.w(), 4_tv2);
    EXPECT_EQ(r2.h(), 5_tv3);
}

TEST(RectTest, Set) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> r;
    r.set(2_tv0, 4_tv2, 3_tv1, 5_tv3);

    EXPECT_EQ(r.x(), 2_tv0);
    EXPECT_EQ(r.y(), 3_tv1);
    EXPECT_EQ(r.w(), 4_tv2);
    EXPECT_EQ(r.h(), 5_tv3);
}

TEST(RectTest, SetXYWH) {
    bmp::rect<typed_value<0>, typed_value<2>, typed_value<1>, typed_value<3>> r;
    r.set_x(2_tv0);
    r.set_y(3_tv1);
    r.set_w(4_tv2);
    r.set_h(5_tv3);

    EXPECT_EQ(r.x(), 2_tv0);
    EXPECT_EQ(r.y(), 3_tv1);
    EXPECT_EQ(r.w(), 4_tv2);
    EXPECT_EQ(r.h(), 5_tv3);
}

TEST(RectTest, SetLTRB) {
    bmp::rect r(12_tv0, 21_tv0, 16_tv1, 28_tv1);

    EXPECT_EQ(r.x(), 12_tv0);
    EXPECT_EQ(r.y(), 16_tv1);
    EXPECT_EQ(r.w(), 21_tv0);
    EXPECT_EQ(r.h(), 28_tv1);

    EXPECT_EQ(r.pos(),  bmp::point(12_tv0, 16_tv1));
    EXPECT_EQ(r.size(), bmp::size(21_tv0, 28_tv1));

    EXPECT_EQ(r.l(), 12_tv0);
    EXPECT_EQ(r.t(), 16_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    EXPECT_EQ(r.lt(), bmp::point(12_tv0, 16_tv1));
    EXPECT_EQ(r.rt(), bmp::point(32_tv0, 16_tv1));
    EXPECT_EQ(r.lb(), bmp::point(12_tv0, 43_tv1));
    EXPECT_EQ(r.rb(), bmp::point(32_tv0, 43_tv1));

    r.set_l(10_tv0);

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 16_tv1);
    EXPECT_EQ(r.w(), 23_tv0);
    EXPECT_EQ(r.h(), 28_tv1);

    EXPECT_EQ(r.pos(),  bmp::point(10_tv0, 16_tv1));
    EXPECT_EQ(r.size(), bmp::size(23_tv0, 28_tv1));

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 16_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    EXPECT_EQ(r.lt(), bmp::point(10_tv0, 16_tv1));
    EXPECT_EQ(r.rt(), bmp::point(32_tv0, 16_tv1));
    EXPECT_EQ(r.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(r.rb(), bmp::point(32_tv0, 43_tv1));

    r.set_t(20_tv1);

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 20_tv1);
    EXPECT_EQ(r.w(), 23_tv0);
    EXPECT_EQ(r.h(), 24_tv1);

    EXPECT_EQ(r.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.size(), bmp::size(23_tv0, 24_tv1));

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 20_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    EXPECT_EQ(r.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.rt(), bmp::point(32_tv0, 20_tv1));
    EXPECT_EQ(r.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(r.rb(), bmp::point(32_tv0, 43_tv1));

    r.set_r(35_tv0);

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 20_tv1);
    EXPECT_EQ(r.w(), 26_tv0);
    EXPECT_EQ(r.h(), 24_tv1);

    EXPECT_EQ(r.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.size(), bmp::size(26_tv0, 24_tv1));

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 20_tv1);
    EXPECT_EQ(r.r(), 35_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    EXPECT_EQ(r.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.rt(), bmp::point(35_tv0, 20_tv1));
    EXPECT_EQ(r.lb(), bmp::point(10_tv0, 43_tv1));
    EXPECT_EQ(r.rb(), bmp::point(35_tv0, 43_tv1));

    r.set_b(57_tv1);

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 20_tv1);
    EXPECT_EQ(r.w(), 26_tv0);
    EXPECT_EQ(r.h(), 38_tv1);

    EXPECT_EQ(r.pos(),  bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.size(), bmp::size(26_tv0, 38_tv1));

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 20_tv1);
    EXPECT_EQ(r.r(), 35_tv0);
    EXPECT_EQ(r.b(), 57_tv1);

    EXPECT_EQ(r.lt(), bmp::point(10_tv0, 20_tv1));
    EXPECT_EQ(r.rt(), bmp::point(35_tv0, 20_tv1));
    EXPECT_EQ(r.lb(), bmp::point(10_tv0, 57_tv1));
    EXPECT_EQ(r.rb(), bmp::point(35_tv0, 57_tv1));
}

TEST(RectTest, SetLTRBPoints) {
    bmp::rect r(12_tv0, 21_tv0, 16_tv1, 28_tv1);

    EXPECT_EQ(r.x(), 12_tv0);
    EXPECT_EQ(r.y(), 16_tv1);
    EXPECT_EQ(r.w(), 21_tv0);
    EXPECT_EQ(r.h(), 28_tv1);

    EXPECT_EQ(r.l(), 12_tv0);
    EXPECT_EQ(r.t(), 16_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    r.set_lt(bmp::point(10_tv0, 20_tv1));

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 20_tv1);
    EXPECT_EQ(r.w(), 23_tv0);
    EXPECT_EQ(r.h(), 24_tv1);

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 20_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);

    r.set_rb(bmp::point(35_tv0, 57_tv1));

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 20_tv1);
    EXPECT_EQ(r.w(), 26_tv0);
    EXPECT_EQ(r.h(), 38_tv1);

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 20_tv1);
    EXPECT_EQ(r.r(), 35_tv0);
    EXPECT_EQ(r.b(), 57_tv1);

    r.set_rt(bmp::point(32_tv0, 16_tv1));

    EXPECT_EQ(r.x(), 10_tv0);
    EXPECT_EQ(r.y(), 16_tv1);
    EXPECT_EQ(r.w(), 23_tv0);
    EXPECT_EQ(r.h(), 42_tv1);

    EXPECT_EQ(r.l(), 10_tv0);
    EXPECT_EQ(r.t(), 16_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 57_tv1);

    r.set_lb(bmp::point(12_tv0, 43_tv1));

    EXPECT_EQ(r.x(), 12_tv0);
    EXPECT_EQ(r.y(), 16_tv1);
    EXPECT_EQ(r.w(), 21_tv0);
    EXPECT_EQ(r.h(), 28_tv1);

    EXPECT_EQ(r.l(), 12_tv0);
    EXPECT_EQ(r.t(), 16_tv1);
    EXPECT_EQ(r.r(), 32_tv0);
    EXPECT_EQ(r.b(), 43_tv1);
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


TEST(RectTest, TypeCast) {
    EXPECT_EQ(static_cast<bmp::rect<int>>(bmp::rect(3.3, 4.4, 5.5, 6.6)), bmp::rect(3, 4, 5, 6));
    EXPECT_EQ((static_cast<bmp::rect<int, unsigned>>(bmp::rect(3.3, 4.4, 5.5, 6.6))),
        bmp::rect(3, 4u, 5, 6u));
    EXPECT_EQ((static_cast<bmp::rect<int, unsigned>>(bmp::rect(3.3, 4.4, 5.5, 6.6))),
        bmp::rect(3, 4u, 5, 6u));
    EXPECT_EQ((static_cast<bmp::rect<int, unsigned, float>>(bmp::rect(3.3, 4.4, 5.5, 6.6))),
        bmp::rect(3, 4u, 5.5f, 6u));
    EXPECT_EQ((static_cast<bmp::rect<int, unsigned, float, long>>(bmp::rect(3.3, 4.4, 5.5, 6.6))),
        bmp::rect(3, 4u, 5.5f, 6l));
}

TEST(RectTest, ContainsPoint) {
    bmp::rect r(2, 3, 4u, 5u);

    EXPECT_TRUE(contains(r, bmp::point(2, 4u)));
    EXPECT_TRUE(contains(r, bmp::point(4, 4u)));
    EXPECT_TRUE(contains(r, bmp::point(2, 8u)));
    EXPECT_TRUE(contains(r, bmp::point(4, 8u)));

    EXPECT_FALSE(contains(r, bmp::point(1, 4u)));
    EXPECT_FALSE(contains(r, bmp::point(2, 3u)));
    EXPECT_FALSE(contains(r, bmp::point(5, 4u)));
    EXPECT_FALSE(contains(r, bmp::point(4, 3u)));
    EXPECT_FALSE(contains(r, bmp::point(1, 8u)));
    EXPECT_FALSE(contains(r, bmp::point(2, 9u)));
    EXPECT_FALSE(contains(r, bmp::point(5, 8u)));
    EXPECT_FALSE(contains(r, bmp::point(4, 9u)));
}

TEST(RectTest, ContainsRect) {
    bmp::rect r(2, 3, 4u, 5u);

    EXPECT_TRUE(contains(r, bmp::rect(2, 3, 4u, 5u)));

    EXPECT_FALSE(contains(r, bmp::rect(1, 4, 4u, 5u)));
    EXPECT_FALSE(contains(r, bmp::rect(2, 4, 4u, 5u)));
    EXPECT_FALSE(contains(r, bmp::rect(2, 3, 3u, 6u)));
    EXPECT_FALSE(contains(r, bmp::rect(2, 3, 4u, 6u)));

    EXPECT_TRUE(contains(bmp::rect(1, 4, 4u, 5u), r));
    EXPECT_TRUE(contains(bmp::rect(2, 4, 4u, 5u), r));
    EXPECT_TRUE(contains(bmp::rect(2, 3, 3u, 6u), r));
    EXPECT_TRUE(contains(bmp::rect(2, 3, 4u, 6u), r));
}

TEST(RectTest, JoinRects) {
    bmp::rect r(2, 3, 4u, 5u);

    EXPECT_EQ(join(r, bmp::rect(2, 3, 4u, 5u)), bmp::rect(2, 3, 4u, 5u));

    EXPECT_EQ(join(r, bmp::rect(3, 2, 4u, 5u)), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(r, bmp::rect(2, 2, 4u, 5u)), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(r, bmp::rect(2, 3, 5u, 4u)), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(r, bmp::rect(2, 3, 4u, 4u)), bmp::rect(2, 3, 4u, 5u));

    EXPECT_EQ(join(bmp::rect(3, 2, 4u, 5u), r), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(bmp::rect(2, 2, 4u, 5u), r), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(bmp::rect(2, 3, 5u, 4u), r), bmp::rect(2, 3, 4u, 5u));
    EXPECT_EQ(join(bmp::rect(2, 3, 4u, 4u), r), bmp::rect(2, 3, 4u, 5u));

    EXPECT_EQ(join(r, bmp::rect(1, 3, 4u, 5u)), bmp::rect(1, 4, 4u, 5u));
    EXPECT_EQ(join(r, bmp::rect(2, 4, 4u, 5u)), bmp::rect(2, 4, 4u, 5u));
    EXPECT_EQ(join(r, bmp::rect(2, 3, 3u, 5u)), bmp::rect(2, 3, 3u, 6u));
    EXPECT_EQ(join(r, bmp::rect(2, 3, 4u, 6u)), bmp::rect(2, 3, 4u, 6u));

    EXPECT_EQ(join(bmp::rect(1, 3, 4u, 5u), r), bmp::rect(1, 4, 4u, 5u));
    EXPECT_EQ(join(bmp::rect(2, 4, 4u, 5u), r), bmp::rect(2, 4, 4u, 5u));
    EXPECT_EQ(join(bmp::rect(2, 3, 3u, 5u), r), bmp::rect(2, 3, 3u, 6u));
    EXPECT_EQ(join(bmp::rect(2, 3, 4u, 6u), r), bmp::rect(2, 3, 4u, 6u));
}
