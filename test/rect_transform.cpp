#include <bitmap/rect_transform.hpp>
#include <bitmap/matrix3x3_io.hpp>
#include <bitmap/point_io.hpp>

#include <gtest/gtest.h>

#include <array>


bool nearly_eq(bmp::point< long double > const& p1, bmp::point< long double > const& p2){
	return
		std::abs(p1.x() - p2.x()) < 0.001 &&
		std::abs(p1.y() - p2.y()) < 0.001;
}

TEST(RectTransformTest, Test){
	std::array< bmp::point< long double >, 4 > from
		{{{84, 93}, {166, 100}, {90, 210}, {163, 200}}};
	std::array< bmp::point< long double >, 4 > to
		{{{10, 10}, {20, 10}, {10, 20}, {20, 20}}};

	auto const c = bmp::rect_transform_homography(from, to);
	EXPECT_TRUE(nearly_eq(to[0], convert(c, from[0])));
	EXPECT_TRUE(nearly_eq(to[1], convert(c, from[1])));
	EXPECT_TRUE(nearly_eq(to[2], convert(c, from[2])));
	EXPECT_TRUE(nearly_eq(to[3], convert(c, from[3])));
}
