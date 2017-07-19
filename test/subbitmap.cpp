#include <bitmap/subbitmap.hpp>

#include <gtest/gtest.h>


template < typename F >
auto calc(std::size_t const w, std::size_t const h, F const& f){
	bitmap::bitmap< float > bmp(w, h);
	for(std::size_t y = 0; y < h; ++y){
		for(std::size_t x = 0; x < w; ++x){
			bmp(x, y) = f(x + 1, y + 1);
		}
	}
	return bmp;
}

using bitmap::rect;


TEST(SubBitmapTest, IntegralThrowing){
	auto bmp = calc(3, 2, [](auto x, auto y){ return (1 + x) * y; });

	EXPECT_EQ(
		subbitmap(bmp, rect{0, 0, 3, 2}),
		calc(3, 2, [](auto x, auto y){ return (1 + x) * y; })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{0, 0, 1, 1}),
		calc(1, 1, [](auto, auto){ return 2; })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{1, 0, 1, 1}),
		calc(1, 1, [](auto, auto){ return 3; })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{0, 1, 1, 1}),
		calc(1, 1, [](auto, auto){ return 4; })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{0, 1, 2, 1}),
		calc(2, 1, [](auto x, auto y){ return (1 + x) * (1 + y); })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{1, 0, 1, 2}),
		calc(1, 2, [](auto x, auto y){ return (2 + x) * y; })
	);

	EXPECT_EQ(
		subbitmap(bmp, rect{2, 1, 1, 1}),
		calc(1, 1, [](auto, auto){ return 8; })
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{0, 0, -1, 1}),
		std::logic_error
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{0, 0, 1, -1}),
		std::logic_error
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{0, 0, -1, -1}),
		std::logic_error
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{-1, 0, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{0, -1, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{-1, -1, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{3, 1, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{2, 2, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{3, 2, 1, 1}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{0, 1, 3, 2}),
		std::out_of_range
	);

	EXPECT_THROW(
		subbitmap(bmp, rect{1, 0, 3, 2}),
		std::out_of_range
	);
}
