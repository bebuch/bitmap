#include <bitmap/rect.hpp>

#include <gtest/gtest.h>


struct move_int {
    int v;

    move_int()
        : v(0) {}

    move_int(int v)
        : v(v) {}

    move_int(move_int&& o)
        : v(o.v) {
        o.v = 0;
    }

    move_int& operator=(move_int&& o) {
        v = o.v;
        o.v = 0;
        return *this;
    }
};


TEST(RectTest, DefaultConstruction) {
    bmp::rect<int> s;

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
    EXPECT_EQ(s.width(), 0);
    EXPECT_EQ(s.height(), 0);
}

TEST(RectTest, WidthHeightConstruction) {
    bmp::rect<int> s(2, 3, 4, 5);

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.width(), 4);
    EXPECT_EQ(s.height(), 5);
}

TEST(RectTest, CopyConstruction) {
    bmp::rect s1(2, 3, 4, 5);
    bmp::rect s2(s1);

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(RectTest, MoveConstruction) {
    bmp::rect s1(2, 3, 4, 5);
    bmp::rect s2(std::move(s1));

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(RectTest, MoveConstructionMoveOnly) {
    bmp::rect<move_int> s1(2, 3, 4, 5);
    bmp::rect<move_int> s2(std::move(s1));

    EXPECT_EQ(s1.x().v, 0);
    EXPECT_EQ(s1.y().v, 0);
    EXPECT_EQ(s1.width().v, 0);
    EXPECT_EQ(s1.height().v, 0);
    EXPECT_EQ(s2.x().v, 2);
    EXPECT_EQ(s2.y().v, 3);
    EXPECT_EQ(s2.width().v, 4);
    EXPECT_EQ(s2.height().v, 5);
}

TEST(RectTest, CopyAssign) {
    bmp::rect<int> s1(2, 3, 4, 5);
    bmp::rect<int> s2;
    s2 = s1;

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(RectTest, MoveAssign) {
    bmp::rect<int> s1(2, 3, 4, 5);
    bmp::rect<int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x(), 2);
    EXPECT_EQ(s1.y(), 3);
    EXPECT_EQ(s1.width(), 4);
    EXPECT_EQ(s1.height(), 5);
    EXPECT_EQ(s2.x(), 2);
    EXPECT_EQ(s2.y(), 3);
    EXPECT_EQ(s2.width(), 4);
    EXPECT_EQ(s2.height(), 5);
}

TEST(RectTest, MoveAssignMoveOnly) {
    bmp::rect<move_int> s1(2, 3, 4, 5);
    bmp::rect<move_int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x().v, 0);
    EXPECT_EQ(s1.y().v, 0);
    EXPECT_EQ(s1.width().v, 0);
    EXPECT_EQ(s1.height().v, 0);
    EXPECT_EQ(s2.x().v, 2);
    EXPECT_EQ(s2.y().v, 3);
    EXPECT_EQ(s2.width().v, 4);
    EXPECT_EQ(s2.height().v, 5);
}

TEST(RectTest, Set) {
    bmp::rect<int> s;
    s.set(2, 3, 4, 5);

    EXPECT_EQ(s.x(), 2);
    EXPECT_EQ(s.y(), 3);
    EXPECT_EQ(s.width(), 4);
    EXPECT_EQ(s.height(), 5);
}

TEST(RectTest, SetMoveOnly) {
    bmp::rect<move_int> s;
    s.set(2, 3, 4, 5);

    EXPECT_EQ(s.x().v, 2);
    EXPECT_EQ(s.y().v, 3);
    EXPECT_EQ(s.width().v, 4);
    EXPECT_EQ(s.height().v, 5);
}

TEST(RectTest, IsPositive) {
    EXPECT_TRUE( bmp::rect(2, 3,  4u,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(2, 3,  4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, 3, -4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, 3,  4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, 3, -4 , -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(2, -3,  4u,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(2, -3,  4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -3, -4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -3,  4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(2, -3, -4 , -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(-2, 3,  4u,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(-2, 3,  4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, 3, -4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, 3,  4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, 3, -4 , -5 ).is_positive());

    EXPECT_TRUE( bmp::rect(-2, -3,  4u,  5u).is_positive());
    EXPECT_TRUE( bmp::rect(-2, -3,  4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -3, -4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -3,  4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::rect(-2, -3, -4 , -5 ).is_positive());
}

TEST(RectTest, Area) {
    EXPECT_EQ(bmp::rect(2, 3,  4u,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3,  4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3, -4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3,  4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3, -4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3, -4,   5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2, 3,  4u, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(-2, 3,  4u,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3,  4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3, -4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3,  4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3, -4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3, -4,   5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, 3,  4u, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(2, -3,  4u,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3,  4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3, -4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3,  4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3, -4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3, -4,   5u).area(), 20u);
    EXPECT_EQ(bmp::rect(2, -3,  4u, -5 ).area(), 20u);

    EXPECT_EQ(bmp::rect(-2, -3,  4u,  5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3,  4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3, -4,   5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3,  4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3, -4,  -5 ).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3, -4,   5u).area(), 20u);
    EXPECT_EQ(bmp::rect(-2, -3,  4u, -5 ).area(), 20u);
}

TEST(RectTest, Compare){
    EXPECT_EQ(bmp::rect(2, 3, 4, 5), bmp::rect(2, 3, 4, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 3, 2, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 3, 4, 3));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(5, 3, 4, 5));
    EXPECT_NE(bmp::rect(2, 3, 4, 5), bmp::rect(2, 4, 4, 5));

    EXPECT_EQ(bmp::rect(2.1, 3u, 4, 5.2f), bmp::rect(2.1, 3u, 4, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 3u, 4, 5.2f), bmp::rect(2.1, 3u, 2, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 3u, 4, 5.2f), bmp::rect(2.1, 3u, 4, 3.2f));
    EXPECT_NE(bmp::rect(2.1, 3u, 4, 5.2f), bmp::rect(2.1, 4u, 4, 5.2f));
    EXPECT_NE(bmp::rect(2.1, 3u, 4, 5.2f), bmp::rect(2.2, 3u, 4, 5.2f));
}
