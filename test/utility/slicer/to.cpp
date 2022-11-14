//==================================================================================================
/*
  KIWAKU - Containers Well Made
  Copyright : KIWAKU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <kwk/utility/container/shape.hpp>

TTS_CASE("Check basic slicing for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;

  constexpr std::size_t d0 = 1, d1 = 2, d2 = 3, d3 = 5;
  auto s2 = kwk::fixed<d2>;
  auto s3 = kwk::fixed<d3>;

  auto t0 = to(d0);
  auto t1 = to(fixed<d1>);
  auto t2 = to(d2);
  auto t3 = to(fixed<d3>);

  auto shp = kwk::of_size(d0, d1, s2, s3);

  TTS_EQUAL( shp(t0, t1, t2, t3) , kwk::of_size(d0, d1, d2, d3));

  // It is possible to get the compile-time extent<0> value, since the value
  // returned by to is static <=> its argument is static
  // (the shape does not have to be static since its value is not part
  // of the computation)
  TTS_TYPED_EQUAL(shp(t0, t1, t2, t3).extent<0>(), d0);
  TTS_TYPED_EQUAL(shp(t0, t1, t2, t3).extent<1>(), fixed<d1>);
  TTS_TYPED_EQUAL(shp(t0, t1, t2, t3).extent<2>(), d2);
  TTS_TYPED_EQUAL(shp(t0, t1, t2, t3).extent<3>(), fixed<d3>);
};

TTS_CASE("Check slicing with end for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  constexpr std::ptrdiff_t d0 = 1, d1 = 3;
  auto s1 = kwk::fixed<d1>;
  auto t0 = to(end);

  auto shp = kwk::of_size(d0, s1);

  TTS_EQUAL( shp(t0, t0), kwk::of_size(d0, s1));
  TTS_TYPED_EQUAL(shp(t0, t0).extent<0>(), d0);
  TTS_TYPED_EQUAL(shp(t0, t0).extent<1>(), fixed<d1>);
};

TTS_CASE("Check slicing with end-n for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  constexpr std::size_t d0 = 1, d1 = 3, d2 = 5, d3 = 7;
  auto s1 = kwk::fixed<d1>;
  auto s3 = kwk::fixed<d3>;

  constexpr std::size_t v0 = 1;
  auto c0 = fixed<v0>;
  auto t0 = to(end-v0);
  auto t1 = to(end-c0);

  auto shp = kwk::of_size(d0, s1, d2, s3);

  TTS_EQUAL( shp(t0, t0, t1, t1), kwk::of_size(d0-v0, d1-v0, d2-c0, d3-c0));

  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<0>(), d0-v0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<1>(), d1-v0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<2>(), d2-c0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<3>(), fixed<d3-c0>);
};

TTS_CASE("Check slicing with end/n for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  constexpr std::size_t d0 = 3, d1 = 5, d2 = 7, d3 = 9;
  auto s1 = kwk::fixed<d1>;
  auto s3 = kwk::fixed<d3>;

  constexpr std::size_t v0 = 2;
  auto c0 = fixed<v0>;
  auto t0 = to(end/v0);
  auto t1 = to(end/c0);

  auto shp = kwk::of_size(d0, s1, d2, s3);

  TTS_EQUAL( shp(t0, t0, t1, t1), kwk::of_size(d0/v0, d1/v0, d2/c0, d3/c0));

  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<0>(), d0/v0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<1>(), d1/v0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<2>(), d2/c0);
  TTS_TYPED_EQUAL(shp(t0, t0, t1, t1).extent<3>(), fixed<d3/c0>);
};

TTS_CASE("Check slicing with (k * end / q) for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  constexpr std::size_t d0 = 3, d1 = 5, d2 = 7, d3 = 9, d4 = 11, d5 = 13, d6 = 15, d7 = 17;
  auto s4 = kwk::fixed<d4>;
  auto s5 = kwk::fixed<d5>;
  auto s6 = kwk::fixed<d6>;
  auto s7 = kwk::fixed<d7>;

  constexpr std::size_t f = 2;
  constexpr std::size_t d = 5;
  auto fc = fixed<f>;
  auto dc = fixed<d>;

  auto tdd = to(end*f/d);
  auto tdc = to(end*f/dc);
  auto tcd = to(end*fc/d);
  auto tcc = to(end*fc/dc);

  auto shp = kwk::of_size(d0, d1, d2, d3, s4, s5, s6, s7);

  auto sliced = shp(tdd, tdc, tcd, tcc, tdd, tdc, tcd, tcc);
  TTS_EQUAL ( sliced
            , kwk::of_size(d0*f/d, d1*f/d, d2*f/d, d3*f/d, d4*f/d, d5*f/d, d6*f/d, d7*f/d)
            );

  TTS_TYPED_EQUAL(sliced.extent<0>(), d0*f/d);
  TTS_TYPED_EQUAL(sliced.extent<1>(), d1*f/d);
  TTS_TYPED_EQUAL(sliced.extent<2>(), d2*f/d);
  TTS_TYPED_EQUAL(sliced.extent<3>(), d3*f/d);
  TTS_TYPED_EQUAL(sliced.extent<4>(), d4*f/d);
  TTS_TYPED_EQUAL(sliced.extent<5>(), d5*f/d);
  TTS_TYPED_EQUAL(sliced.extent<6>(), d6*f/d);
  TTS_TYPED_EQUAL(sliced.extent<7>(), fixed<d7*f/d>);
};

TTS_CASE("Check slicing with (k * end / q + dynamic_offset) for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  constexpr std::size_t od = 2;
  constexpr std::size_t d0 = 5, d1 = 7, d2 = 9, d3 = 11, d4 = 13, d5 = 15, d6 = 17, d7 = 19;
  auto s4 = kwk::fixed<d4>;
  auto s5 = kwk::fixed<d5>;
  auto s6 = kwk::fixed<d6>;
  auto s7 = kwk::fixed<d7>;

  constexpr std::size_t f = 2;
  constexpr std::size_t d = 5;
  auto fc = fixed<f>;
  auto dc = fixed<d>;

  auto tdd = to(end*f /d  + od);
  auto tdc = to(end*f /dc + od);
  auto tcd = to(end*fc/d  + od);
  auto tcc = to(end*fc/dc + od);

  auto shp = kwk::of_size(d0, d1, d2, d3, s4, s5, s6, s7);

  auto sliced = shp(tdd, tdc, tcd, tcc, tdd, tdc, tcd, tcc);
  TTS_EQUAL ( sliced
            , kwk::of_size(d0*f/d+od, d1*f/d+od, d2*f/d+od
            , d3*f/d+od, d4*f/d+od, d5*f/d+od, d6*f/d+od, d7*f/d+od)
            );

  TTS_TYPED_EQUAL(sliced.extent<0>(), d0*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<1>(), d1*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<2>(), d2*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<3>(), d3*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<4>(), d4*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<5>(), d5*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<6>(), d6*f/d+od);
  TTS_TYPED_EQUAL(sliced.extent<7>(), d7*f/d+od);
};

TTS_CASE("Check slicing with (k * end / q + static_offset) for kwk::to")
{
  using namespace kwk::literals;
  using kwk::to;
  using kwk::fixed;
  using kwk::end;

  auto oc = fixed<2UL>;
  constexpr std::size_t d0 = 5, d1 = 7, d2 = 9, d3 = 11, d4 = 13, d5 = 15, d6 = 17, d7 = 19;
  auto s4 = kwk::fixed<d4>;
  auto s5 = kwk::fixed<d5>;
  auto s6 = kwk::fixed<d6>;
  auto s7 = kwk::fixed<d7>;

  constexpr std::size_t f = 2;
  constexpr std::size_t d = 5;
  auto fc = fixed<f>;
  auto dc = fixed<d>;

  auto tdd = to(end*f /d  + oc);
  auto tdc = to(end*f /dc + oc);
  auto tcd = to(end*fc/d  + oc);
  auto tcc = to(end*fc/dc + oc);

  auto shp = kwk::of_size(d0, d1, d2, d3, s4, s5, s6, s7);

  auto sliced = shp(tdd, tdc, tcd, tcc, tdd, tdc, tcd, tcc);
  TTS_EQUAL ( sliced
            , kwk::of_size(d0*f/d+oc, d1*f/d+oc, d2*f/d+oc
            , d3*f/d+oc, d4*f/d+oc, d5*f/d+oc, d6*f/d+oc, d7*f/d+oc)
            );

  TTS_TYPED_EQUAL(sliced.extent<0>(), d0*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<1>(), d1*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<2>(), d2*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<3>(), d3*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<4>(), d4*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<5>(), d5*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<6>(), d6*f/d+oc);
  TTS_TYPED_EQUAL(sliced.extent<7>(), fixed<d7*f/d+oc>);
};
