//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>
#include <cmath>

//==================================================================================================
// Tests for eve::is_denormal
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return 2*eve::smallestposval(tgt);
};

auto lastdenormal = []<typename T>(eve::as<T> const & tgt)
{
  return eve::prev(eve::smallestposval(tgt));
};

EVE_TEST( "Check behavior of eve::is_denormal(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::smallestposval, mini)
                              , eve::test::randoms(eve::mindenormal, lastdenormal)
                              , eve::test::randoms(eve::zero, mini)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto vda0 = eve::var(a0);
  auto vda1 = eve::var(a1);
  auto vda2 = eve::var(a2);

  TTS_EQUAL(eve::is_denormal(vda0), eve::false_(eve::as(a0)));
  TTS_EQUAL(eve::is_denormal[t](vda0), eve::if_else(t, eve::is_denormal(a0), eve::false_(eve::as(a0))));
  TTS_EQUAL(eve::is_denormal(vda1), eve::logical<T>{eve::platform::supports_denormals});

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_EQUAL(eve::is_denormal(vda2), map([](auto e) -> eve::logical<v_t> { return  std::fpclassify(e) == FP_SUBNORMAL; }, a2));
  }
  else
  {
    TTS_EQUAL(eve::is_denormal(vda2), eve::false_(eve::as(a2)));
  }
};
