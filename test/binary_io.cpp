#include <bitmap/binary_write.hpp>
#include <bitmap/binary_read.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <random>
#include <algorithm>


constexpr std::size_t header_size = 24;

using bmp::bitmap;
using bmp::binary_read;
using bmp::binary_write;
namespace pixel = bmp::pixel;

template < typename T >
auto make(std::size_t w, std::size_t h){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	using value_type = pixel::channel_type_t< T >;
	using limits = std::numeric_limits< value_type >;
	using uniform_distribution = std::conditional_t<
			std::is_floating_point_v< value_type >,
			std::uniform_real_distribution< value_type >,
			std::uniform_int_distribution< value_type >
		>;
	static uniform_distribution dis(limits::min(), limits::max());

	bitmap< T > result(w, h);
	std::generate(result.begin(), result.end(), []{
		T v;
		for(std::size_t i = 0; i < pixel::channel_count_v< T >; ++i){
			auto& c = *(reinterpret_cast< value_type* >(&v) + i);
			c = dis(gen);
		}
		return v;
	});
	return result;
}

template <>
auto make< bool >(std::size_t w, std::size_t h){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	using limits = std::numeric_limits< signed char >;
	static std::uniform_int_distribution< signed char >
		dis(limits::min(), limits::max());

	bitmap< bool > result(w, h);
	std::generate(result.begin(), result.end(), []{
		return dis(gen) < 0;
	});
	return result;
}


TEST(BinaryIOTest, BoolSizePassTest){
	auto img = make< bool >(64, 8);
	std::stringstream s;
	binary_write(img, s);
	EXPECT_EQ(s.str().size(), header_size + 64);
	auto img2 = binary_read< bool >(s);
	EXPECT_EQ(img, img2);
}

TEST(BinaryIOTest, BoolSizePlus1Test){
	auto img = make< bool >(129, 1);
	std::stringstream s;
	binary_write(img, s);
	EXPECT_EQ(s.str().size(), header_size + 17);
	auto img2 = binary_read< bool >(s);
	EXPECT_EQ(img, img2);
}

TEST(BinaryIOTest, BoolSizeMinus1Test){
	auto img = make< bool >(1, 127);
	std::stringstream s;
	binary_write(img, s);
	EXPECT_EQ(s.str().size(), header_size + 16);
	auto img2 = binary_read< bool >(s);
	EXPECT_EQ(img, img2);
}


template < typename T >
struct read_write_test: public ::testing::Test{
	using type = T;
};

using all_types = ::testing::Types<
		std::int8_t
		, std::uint8_t
		, std::int16_t
		, std::uint16_t
		, std::int32_t
		, std::uint32_t
		, std::int64_t
		, std::uint64_t
		, pixel::ga8
		, pixel::ga16
		, pixel::ga32
		, pixel::ga64
		, pixel::ga8u
		, pixel::ga16u
		, pixel::ga32u
		, pixel::ga64u
		, pixel::rgb8
		, pixel::rgb16
		, pixel::rgb32
		, pixel::rgb64
		, pixel::rgb8u
		, pixel::rgb16u
		, pixel::rgb32u
		, pixel::rgb64u
		, pixel::rgba8
		, pixel::rgba16
		, pixel::rgba32
		, pixel::rgba64
		, pixel::rgba8u
		, pixel::rgba16u
		, pixel::rgba32u
		, pixel::rgba64u
		, float
		, double
		, pixel::ga32f
		, pixel::ga64f
		, pixel::rgb32f
		, pixel::rgb64f
		, pixel::rgba32f
		, pixel::rgba64f
	>;

TYPED_TEST_CASE(read_write_test, all_types);
TYPED_TEST(read_write_test, RWTest){
	using type = typename TestFixture::type;
	auto img = make< type >(9, 9);
	std::stringstream s;
	binary_write(img, s);
	EXPECT_EQ(s.str().size(), header_size + img.point_count() * sizeof(type));
	auto img2 = binary_read< type >(s);
	EXPECT_EQ(img, img2);
}


template < typename T >
struct endian_read_write_test: public ::testing::Test{
	using type = T;
};

using int_types = ::testing::Types<
		std::int8_t
		, std::uint8_t
		, std::int16_t
		, std::uint16_t
		, std::int32_t
		, std::uint32_t
		, std::int64_t
		, std::uint64_t
		, pixel::ga8
		, pixel::ga16
		, pixel::ga32
		, pixel::ga64
		, pixel::ga8u
		, pixel::ga16u
		, pixel::ga32u
		, pixel::ga64u
		, pixel::rgb8
		, pixel::rgb16
		, pixel::rgb32
		, pixel::rgb64
		, pixel::rgb8u
		, pixel::rgb16u
		, pixel::rgb32u
		, pixel::rgb64u
		, pixel::rgba8
		, pixel::rgba16
		, pixel::rgba32
		, pixel::rgba64
		, pixel::rgba8u
		, pixel::rgba16u
		, pixel::rgba32u
		, pixel::rgba64u
	>;
TYPED_TEST_CASE(endian_read_write_test, int_types);

TYPED_TEST(endian_read_write_test, LittleRWTest){
	using type = typename TestFixture::type;
	auto img = make< type >(9, 9);
	std::stringstream s;
	binary_write(img, s, boost::endian::order::little);
	EXPECT_EQ(s.str().size(), header_size + img.point_count() * sizeof(type));
	auto img2 = binary_read< type >(s);
	EXPECT_EQ(img, img2);
}

TYPED_TEST(endian_read_write_test, BigRWTest){
	using type = typename TestFixture::type;
	auto img = make< type >(9, 9);
	std::stringstream s;
	binary_write(img, s, boost::endian::order::big);
	EXPECT_EQ(s.str().size(), header_size + img.point_count() * sizeof(type));
	auto img2 = binary_read< type >(s);
	EXPECT_EQ(img, img2);
}
