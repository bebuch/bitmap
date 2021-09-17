#include <bitmap/subbitmap.hpp>

#include <gtest/gtest.h>

#include <array>


template <typename F>
auto calc(std::size_t const w, std::size_t const h, F const& f) {
    bmp::bitmap<float> bmp(w, h);
    for(std::size_t y = 0; y < h; ++y) {
        for(std::size_t x = 0; x < w; ++x) {
            bmp(x, y) = f(x + 1, y + 1);
        }
    }
    return bmp;
}

using bmp::rect;


// TODO: Use all possible integer types
TEST(SubBitmapTest, IntIntThrow) {
    auto bmp = calc(3, 2, [](auto x, auto y) { return (1 + x) * y; });

    EXPECT_EQ(subbitmap(bmp, rect{0, 3, 0, 2}), calc(3, 2, [](auto x, auto y) {
                  return (1 + x) * y;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 1, 0, 1}), calc(1, 1, [](auto, auto) { return 2; }));

    EXPECT_EQ(subbitmap(bmp, rect{1, 1, 0, 1}), calc(1, 1, [](auto, auto) { return 3; }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 1, 1, 1}), calc(1, 1, [](auto, auto) { return 4; }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 2, 1, 1}), calc(2, 1, [](auto x, auto y) {
                  return (1 + x) * (1 + y);
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1, 1, 0, 2}), calc(1, 2, [](auto x, auto y) {
                  return (2 + x) * y;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{2, 1, 1, 1}), calc(1, 1, [](auto, auto) { return 8; }));

    EXPECT_THROW(subbitmap(bmp, rect{0, -1, 0, 1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0, 1, 0, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0, -1, 0, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{-1, 1, 0, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0, 1, -1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{-1, 1, -1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3, 1, 1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{2, 1, 2, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3, 1, 2, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0, 3, 1, 2}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{1, 3, 0, 2}), std::out_of_range);
}

// TODO: Use all possible integer types
TEST(SubBitmapTest, FloatIFloatIThrow) {
    auto bmp = calc(3, 2, [](auto x, auto y) { return (1 + x) * y; });

    EXPECT_EQ(subbitmap(bmp, rect{0., 3, 0., 2}), calc(3, 2, [](auto x, auto y) {
                  return (1 + x) * y;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0., 1, 0., 1}), calc(1, 1, [](auto, auto) { return 2; }));

    EXPECT_EQ(subbitmap(bmp, rect{1., 1, 0., 1}), calc(1, 1, [](auto, auto) { return 3; }));

    EXPECT_EQ(subbitmap(bmp, rect{0., 1, 1., 1}), calc(1, 1, [](auto, auto) { return 4; }));

    EXPECT_EQ(subbitmap(bmp, rect{0., 2, 1., 1}), calc(2, 1, [](auto x, auto y) {
                  return (1 + x) * (1 + y);
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1., 1, 0., 2}), calc(1, 2, [](auto x, auto y) {
                  return (2 + x) * y;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{2., 1, 1., 1}), calc(1, 1, [](auto, auto) { return 8; }));

    EXPECT_THROW(subbitmap(bmp, rect{0., -1, 0., 1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0., 1, 0., -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0., -1, 0., -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{-1., 1, 0., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0., 1, -1., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{-1., 1, -1., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3., 1, 1., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{2., 1, 2., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3., 1, 2., 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0., 3, 1., 2}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{1., 3, 0., 2}), std::out_of_range);
}


// TODO; use all possible float types
TEST(SubBitmapTest, IntFloatThrow) {
    auto bmp = calc(3, 3, [](auto x, auto y) { return (1 + x) * y; });

    EXPECT_EQ(subbitmap(bmp, rect{0, 3, 0.25, 2}), calc(3, 2, [](auto x, auto y) {
                  return std::array<std::array<double, 3>, 2>{
                      {std::array<double, 3>{{3.5, 5.25, 7}},
                       std::array<double, 3>{{5.5, 8.25, 11}}}}[y - 1][x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 1, 0.25, 1}), calc(1, 1, [](auto, auto) { return 3.5; }));

    EXPECT_EQ(subbitmap(bmp, rect{1, 1, 0.25, 1}), calc(1, 1, [](auto, auto) { return 5.25; }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 1, 1.25, 1}), calc(1, 1, [](auto, auto) { return 5.5; }));

    EXPECT_EQ(subbitmap(bmp, rect{0, 2, 1.25, 1}), calc(2, 1, [](auto x, auto) {
                  return std::array<double, 2>{{5.5, 8.25}}[x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1, 1, 0.25, 2}), calc(1, 2, [](auto, auto y) {
                  return std::array<double, 2>{{5.25, 8.25}}[y - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{2, 1, 1.25, 1}), calc(1, 1, [](auto, auto) { return 11; }));

    EXPECT_THROW(subbitmap(bmp, rect{0, -1, 0.25, 1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0, 1,0.25,  -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0, -1, 0.25, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{-1, 1, 0.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0, 1, -0.75, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{-1, 1, -0.75, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3, 1, 1.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{2, 1, 2.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3, 1, 2.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0, 3, 1.25, 2}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{1, 3, 0.25, 2}), std::out_of_range);
}

// TODO; use all possible float types
TEST(SubBitmapTest, FloatIntThrow) {
    auto bmp = calc(4, 2, [](auto x, auto y) { return (1 + x) * y; });

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 3, 0, 2}), calc(3, 2, [](auto x, auto y) {
                  return std::array<std::array<double, 3>, 2>{
                      {std::array<double, 3>{{2.75, 3.75, 4.75}},
                       std::array<double, 3>{{5.5, 7.5, 9.5}}}}[y - 1][x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 1, 0, 1}), calc(1, 1, [](auto, auto) { return 2.75; }));

    EXPECT_EQ(subbitmap(bmp, rect{1.25, 1, 0, 1}), calc(1, 1, [](auto, auto) { return 3.75; }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 1, 1, 1}), calc(1, 1, [](auto, auto) { return 5.5; }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 2, 1, 1}), calc(2, 1, [](auto x, auto) {
                  return std::array<double, 2>{{5.5, 7.5}}[x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1.25, 1, 0, 2}), calc(1, 2, [](auto, auto y) {
                  return std::array<double, 2>{{3.75, 7.5}}[y - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{2.25, 1, 1, 1}), calc(1, 1, [](auto, auto) { return 9.5; }));

    EXPECT_THROW(subbitmap(bmp, rect{0.25, -1, 0, 1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 1, 0, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, -1, 0, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{-0.75, 1, 0, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 1, -1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{-0.75, 1, -1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3.25, 1, 1, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{2.25, 1, 2, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3.25, 1, 2, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 3, 1, 2}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{1.25, 3, 0, 2}), std::out_of_range);
}

// TODO; use all possible float types
TEST(SubBitmapTest, FloatFloatThrow) {
    auto bmp = calc(4, 3, [](auto x, auto y) { return (1 + x) * y; });

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 3, 0.25, 2}), calc(3, 2, [](auto x, auto y) {
                  return std::array<std::array<double, 3>, 2>{
                      {std::array<double, 3>{{2.8125, 4.0625, 5.3125}},
                       std::array<double, 3>{{5.0625, 7.3125, 9.5625}}}}[y - 1][x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 1, 0.25, 1}), calc(1, 1, [](auto, auto) {
                  return 2.8125;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1.25, 1, 0.25, 1}), calc(1, 1, [](auto, auto) {
                  return 4.0625;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 1, 1.25, 1}), calc(1, 1, [](auto, auto) {
                  return 5.0625;
              }));

    EXPECT_EQ(subbitmap(bmp, rect{0.25, 2, 1.25, 1}), calc(2, 1, [](auto x, auto) {
                  return std::array<double, 2>{{5.0625, 7.3125}}[x - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{1.25, 1, 0.25, 2}), calc(1, 2, [](auto, auto y) {
                  return std::array<double, 2>{{4.0625, 7.3125}}[y - 1];
              }));

    EXPECT_EQ(subbitmap(bmp, rect{2.25, 1, 1.25, 1}), calc(1, 1, [](auto, auto) {
                  return 9.5625;
              }));

    EXPECT_THROW(subbitmap(bmp, rect{0.25, -1, 0.25, 1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 1, 0.25, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, -1, 0.25, -1}), std::logic_error);

    EXPECT_THROW(subbitmap(bmp, rect{-0.75, 1,0.25,  1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 1, -0.75, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{-0.75, 1,-0.75,  1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3.25, 1, 1.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{2.25, 1, 2.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{3.25, 1, 2.25, 1}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{0.25, 3, 1.25, 2}), std::out_of_range);

    EXPECT_THROW(subbitmap(bmp, rect{1.25, 3, 0.25, 2}), std::out_of_range);
}
