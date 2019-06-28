#include <bitmap/size.hpp>

#include <gtest/gtest.h>


struct move_int{
	int v;

	move_int(): v(0) {}

	move_int(int v): v(v) {}

	move_int(move_int&& o): v(o.v) { o.v = 0; }

	move_int& operator=(move_int&& o){ v = o.v; o.v = 0; }
};


TEST(SizeTest, DefaultConstruction){
	bmp::size< int > s;

	EXPECT_EQ(s.width(), 0);
	EXPECT_EQ(s.height(), 0);
}

TEST(SizeTest, WidthHeightConstruction){
	bmp::size< int > s(4, 5);

	EXPECT_EQ(s.width(), 4);
	EXPECT_EQ(s.height(), 5);
}

TEST(SizeTest, CopyConstruction){
	bmp::size< int > s1(4, 5);
	bmp::size< int > s2(s1);

	EXPECT_EQ(s1.width(), 4);
	EXPECT_EQ(s1.height(), 5);
	EXPECT_EQ(s2.width(), 4);
	EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveConstruction){
	bmp::size< int > s1(4, 5);
	bmp::size< int > s2(std::move(s1));

	EXPECT_EQ(s1.width(), 4);
	EXPECT_EQ(s1.height(), 5);
	EXPECT_EQ(s2.width(), 4);
	EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveConstructionMoveOnly){
	bmp::size< move_int > s1(4, 5);
	bmp::size< move_int > s2(std::move(s1));

	EXPECT_EQ(s1.width().v, 0);
	EXPECT_EQ(s1.height().v, 0);
	EXPECT_EQ(s2.width().v, 4);
	EXPECT_EQ(s2.height().v, 5);
}

TEST(SizeTest, CopyAssign){
	bmp::size< int > s1(4, 5);
	bmp::size< int > s2;
	s2 = s1;

	EXPECT_EQ(s1.width(), 4);
	EXPECT_EQ(s1.height(), 5);
	EXPECT_EQ(s2.width(), 4);
	EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveAssign){
	bmp::size< int > s1(4, 5);
	bmp::size< int > s2;
	s2 = std::move(s1);

	EXPECT_EQ(s1.width(), 4);
	EXPECT_EQ(s1.height(), 5);
	EXPECT_EQ(s2.width(), 4);
	EXPECT_EQ(s2.height(), 5);
}

TEST(SizeTest, MoveAssignMoveOnly){
	bmp::size< move_int > s1(4, 5);
	bmp::size< move_int > s2;
	s2 = std::move(s1);

	EXPECT_EQ(s1.width().v, 0);
	EXPECT_EQ(s1.height().v, 0);
	EXPECT_EQ(s2.width().v, 4);
	EXPECT_EQ(s2.height().v, 5);
}

TEST(SizeTest, Set){
	bmp::size< int > s;
	s.set(4, 5);

	EXPECT_EQ(s.width(), 4);
	EXPECT_EQ(s.height(), 5);
}

TEST(SizeTest, SetMoveOnly){
	bmp::size< move_int > s;
	s.set(4, 5);

	EXPECT_EQ(s.width().v, 4);
	EXPECT_EQ(s.height().v, 5);
}

TEST(SizeTest, IsPositive){
	EXPECT_TRUE((bmp::size< unsigned >(4, 5).is_positive()));
	EXPECT_TRUE((bmp::size< int >(4, 5).is_positive()));
	EXPECT_FALSE((bmp::size< int >(-4, 5).is_positive()));
	EXPECT_FALSE((bmp::size< int >(4, -5).is_positive()));
	EXPECT_FALSE((bmp::size< int >(-4, -5).is_positive()));
}

TEST(SizeTest, Area){
	EXPECT_EQ((bmp::size< unsigned >(4, 5).area()), 20);
	EXPECT_EQ((bmp::size< int >(4, 5).area()), 20);
	EXPECT_EQ((bmp::size< int >(-4, 5).area()), 20);
	EXPECT_EQ((bmp::size< int >(4, -5).area()), 20);
	EXPECT_EQ((bmp::size< int >(-4, -5).area()), 20);
	EXPECT_EQ((bmp::size< int, unsigned >(-4, 5).area()), 20);
	EXPECT_EQ((bmp::size< unsigned, int >(4, -5).area()), 20);
}
