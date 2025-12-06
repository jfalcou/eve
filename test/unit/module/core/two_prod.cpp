//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
//== average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior oftwo_prod)",
              eve::test::scalar::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1)
{
  using eve::two_prod;
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t)  == 2)
  {
    using u_t = float;
    auto [a, e] = two_prod(a0, a1);
    u_t da = u_t(a);
    u_t de = u_t(e);
    u_t da0 = u_t(a0);
    u_t da1 = u_t(a1);
    auto dn = [](auto z){return eve::convert(z, eve::as<eve::float16_t>());};
    TTS_EQUALdn((da0*da1), dn(da+de));
  }
  else if constexpr(sizeof(e_t) == 4)
  {
    using u_t = eve::upgrade_t<e_t>;
    auto [a, e] = two_prod(a0, a1);
    u_t da = u_t(a);
    u_t de = u_t(e);
    u_t da0 = u_t(a0);
    u_t da1 = u_t(a1);
    TTS_EQUAL(eve::downgrade(da0*da1), eve::downgrade(da+de));
  }
  else
  {
    using ld_t = long double;
    std::cout << sizeof(ld_t);
    auto [a, e] = two_prod(a0, a1);
    ld_t da = ld_t(a);
    ld_t de = ld_t(e);
    ld_t da0 = ld_t(a0);
    ld_t da1 = ld_t(a1);
    TTS_EQUAL(double(da0*da1), double(da+de));
  }
};


TTS_CASE_WITH("Check behavior of two_prod(wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms( -1000., +1000.),
                            tts::randoms( -1000., +1000.)
                           )
             )
<typename T>(T a0, T a1)
{
  using eve::two_prod;
  if constexpr(sizeof(eve::element_type_t<T>) == 2)
  {
    auto up = [](auto z){return eve::convert(z, eve::as<float>());};
    auto [a, e] = two_prod(a0, a1);
    auto da = up(a);
    auto de = up(e);
    auto da0 = up(a0);
    auto da1 = up(a1);
    auto dn = [](auto z){return eve::convert(z, eve::as<eve::float16_t>());};
    TTS_ULP_EQUAL(dn(da0*da1), dn(da+de), 0.5);
  }
  else if constexpr(sizeof(eve::element_type_t<T>) == 4)
  {
    auto [a, e] = two_prod(a0, a1);
    auto da = eve::upgrade(a);
    auto de = eve::upgrade(e);
    auto da0 = eve::upgrade(a0);
    auto da1 = eve::upgrade(a1);
    TTS_ULP_EQUAL(eve::downgrade(da0*da1), eve::downgrade(da+de), 0.5);
  }
};
