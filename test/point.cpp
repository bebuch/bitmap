#include <bitmap/point.hpp>

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


TEST(PointTest, DefaultConstruction) {
    bmp::point<int> s;

    EXPECT_EQ(s.x(), 0);
    EXPECT_EQ(s.y(), 0);
}

TEST(PointTest, WidthHeightConstruction) {
    bmp::point<int> s(4, 5);

    EXPECT_EQ(s.x(), 4);
    EXPECT_EQ(s.y(), 5);
}

TEST(PointTest, CopyConstruction) {
    bmp::point<int> s1(4, 5);
    bmp::point<int> s2(s1);

    EXPECT_EQ(s1.x(), 4);
    EXPECT_EQ(s1.y(), 5);
    EXPECT_EQ(s2.x(), 4);
    EXPECT_EQ(s2.y(), 5);
}

TEST(PointTest, MoveConstruction) {
    bmp::point<int> s1(4, 5);
    bmp::point<int> s2(std::move(s1));

    EXPECT_EQ(s1.x(), 4);
    EXPECT_EQ(s1.y(), 5);
    EXPECT_EQ(s2.x(), 4);
    EXPECT_EQ(s2.y(), 5);
}

TEST(PointTest, MoveConstructionMoveOnly) {
    bmp::point<move_int> s1(4, 5);
    bmp::point<move_int> s2(std::move(s1));

    EXPECT_EQ(s1.x().v, 0);
    EXPECT_EQ(s1.y().v, 0);
    EXPECT_EQ(s2.x().v, 4);
    EXPECT_EQ(s2.y().v, 5);
}

TEST(PointTest, CopyAssign) {
    bmp::point<int> s1(4, 5);
    bmp::point<int> s2;
    s2 = s1;

    EXPECT_EQ(s1.x(), 4);
    EXPECT_EQ(s1.y(), 5);
    EXPECT_EQ(s2.x(), 4);
    EXPECT_EQ(s2.y(), 5);
}

TEST(PointTest, MoveAssign) {
    bmp::point<int> s1(4, 5);
    bmp::point<int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x(), 4);
    EXPECT_EQ(s1.y(), 5);
    EXPECT_EQ(s2.x(), 4);
    EXPECT_EQ(s2.y(), 5);
}

TEST(PointTest, MoveAssignMoveOnly) {
    bmp::point<move_int> s1(4, 5);
    bmp::point<move_int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s1.x().v, 0);
    EXPECT_EQ(s1.y().v, 0);
    EXPECT_EQ(s2.x().v, 4);
    EXPECT_EQ(s2.y().v, 5);
}

TEST(PointTest, Set) {
    bmp::point<int> s;
    s.set(4, 5);

    EXPECT_EQ(s.x(), 4);
    EXPECT_EQ(s.y(), 5);
}

TEST(PointTest, SetMoveOnly) {
    bmp::point<move_int> s;
    s.set(4, 5);

    EXPECT_EQ(s.x().v, 4);
    EXPECT_EQ(s.y().v, 5);
}

TEST(PointTest, IsPositive) {
    EXPECT_TRUE( bmp::point( 4u,  5u).is_positive());
    EXPECT_TRUE( bmp::point( 4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::point(-4 ,  5 ).is_positive());
    EXPECT_FALSE(bmp::point( 4 , -5 ).is_positive());
    EXPECT_FALSE(bmp::point(-4 , -5 ).is_positive());
}

TEST(PointTest, Compare){
    EXPECT_EQ(bmp::point(4, 5), bmp::point(4, 5));
    EXPECT_NE(bmp::point(4, 5), bmp::point(2, 5));
    EXPECT_NE(bmp::point(4, 5), bmp::point(4, 3));

    EXPECT_EQ(bmp::point(4, 5.2f), bmp::point(4, 5.2f));
    EXPECT_NE(bmp::point(4, 5.2f), bmp::point(2, 5.2f));
    EXPECT_NE(bmp::point(4, 5.2f), bmp::point(4, 3.2f));
}

TEST(PointTest, Plus){
    EXPECT_EQ(bmp::point(14  , 17  ) + bmp::point(2  , 3  ), bmp::point(16  , 20  ));
    EXPECT_EQ(bmp::point(14.2, 17  ) + bmp::point(2.3, 3  ), bmp::point(16.5, 20  ));
    EXPECT_EQ(bmp::point(14  , 17.2) + bmp::point(2  , 3.3), bmp::point(16  , 20.5));
}

TEST(PointTest, Minus){
    EXPECT_EQ(bmp::point(14  , 17  ) - bmp::point(2  , 3  ), bmp::point(      12  ,       14  ));
    EXPECT_EQ(bmp::point(14.2, 17  ) - bmp::point(2.4, 3  ), bmp::point(14.2 - 2.4,       14  ));
    EXPECT_EQ(bmp::point(14  , 17.2) - bmp::point(2  , 3.4), bmp::point(      12  , 17.2 - 3.4));
}

TEST(PointTest, Multiply){
    EXPECT_EQ(bmp::point(14  , 17  ) * bmp::point(2  ,   3), bmp::point(28   , 51   ));
    EXPECT_EQ(bmp::point(14.2, 17  ) * bmp::point(2.3,   3), bmp::point(32.66, 51   ));
    EXPECT_EQ(bmp::point(14  , 17.2) * bmp::point(2  , 3.3), bmp::point(28   , 56.76));
}

TEST(PointTest, Divide){
    EXPECT_EQ(bmp::point(14  , 17  ) / bmp::point(4  , 5  ), bmp::point(3  , 3  ));
    EXPECT_EQ(bmp::point(14.0, 17  ) / bmp::point(4.0, 5  ), bmp::point(3.5, 3  ));
    EXPECT_EQ(bmp::point(14  , 17.0) / bmp::point(4  , 5.0), bmp::point(3  , 3.4));
}

TEST(PointTest, Modulo){
    EXPECT_EQ(bmp::point(14, 15) % bmp::point(4, 6), bmp::point(2, 3));
}
