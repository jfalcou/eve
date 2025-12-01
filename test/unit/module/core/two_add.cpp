//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of two_add(wide)",
              eve::test::scalar::ieee_reals_wf16,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1)
{
  using eve::two_add;
  using e_t = eve::element_type_t<T>;
  using u_t = eve::upgrade_t<e_t>;
  if constexpr(sizeof(e_t) <= 4)
  {
    auto [a, e] = two_add(a0, a1);
    u_t da = u_t(a);
    u_t de = u_t(e);
    u_t da0 = u_t(a0);
    u_t da1 = u_t(a1);
    TTS_EQUAL(da0+da1, (da+de));
  }
  else
  {
    using ld_t = long double;
    std::cout << sizeof(ld_t);
    auto [a, e] = two_add(a0, a1);
    ld_t da = ld_t(a);
    ld_t de = ld_t(e);
    ld_t da0 = ld_t(a0);
    ld_t da1 = ld_t(a1);
    TTS_EQUAL(da0+da1, (da+de));
  }
};

TTS_CASE_WITH("Check behavior of two_add(wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1)
{
  using eve::two_add;
  if constexpr(sizeof(eve::element_type_t<T>) <= 4)
  {
    auto [a, e] = two_add[eve::pedantic](a0, a1);
    auto da = eve::upgrade(a);
    auto de = eve::upgrade(e);
    auto da0 = eve::upgrade(a0);
    auto da1 = eve::upgrade(a1);
    TTS_EQUAL(da0+da1, (da+de));
  }
};
