#include <bitmap/subbitmap.hpp>

#include <gtest/gtest.h>


template < typename F >
auto calc(std::size_t const w, std::size_t const h, F const& f){
	bitmap::bitmap< float > bmp(w, h);
	for(std::size_t y = 0; y < h; ++y){
		for(std::size_t x = 0; x < w; ++x){
			bmp(x, y) = f(x, y);
		}
	}
	return bmp;
}

using bitmap::rect;


TEST(SubBitmapTest, IntegralThrowing){
	auto bmp = calc(3, 2, [](auto x, auto y){ return (1 + x) + y; });

	EXPECT_EQ(
		subbitmap(bmp, rect{0, 0, 3, 2}),
		calc(3, 2, [](auto x, auto y){ return (1 + x) + y; })
	);
}


// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
