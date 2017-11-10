#include <bitmap/rect_transform.hpp>
#include <bitmap/matrix3x3_io.hpp>
#include <bitmap/rect_io.hpp>

#include <io_tools/std_array_io.hpp>

#include <gtest/gtest.h>

#include <array>


bool nearly_eq(bmp::point< double > const& p1, bmp::point< double > const& p2){
	return
		std::abs(p1.x() - p2.x()) < 0.001 &&
		std::abs(p1.y() - p2.y()) < 0.001;
}

TEST(RectTransformTest, Test){
	std::array< bmp::point< double >, 4 > from
		{{{84, 93}, {166, 100}, {90, 210}, {163, 200}}};
	std::array< bmp::point< double >, 4 > to
		{{{10, 10}, {20, 10}, {10, 20}, {20, 20}}};

	auto const c = bmp::rect_transform_homography(from, to);
	EXPECT_TRUE(nearly_eq(to[0], transform(c, from[0])));
	EXPECT_TRUE(nearly_eq(to[1], transform(c, from[1])));
	EXPECT_TRUE(nearly_eq(to[2], transform(c, from[2])));
	EXPECT_TRUE(nearly_eq(to[3], transform(c, from[3])));


	auto const contour
		= transform_image_contour(c, bmp::size< std::size_t >{300, 300});

	{
		using ::io_tools::std_array::operator<<;
		std::cout << contour << '\n';
	}

	auto ic = bmp::image_contour(contour);
	std::cout << ic << '\n';
}
