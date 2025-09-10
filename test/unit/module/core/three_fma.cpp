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
//== mean_value tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mean_value(wide)",
              eve::test::scalar::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1, T a2)
{
  using eve::three_fma;
  if constexpr(sizeof(eve::element_type_t<T>) == 4)
  {
    auto [a, e, f] = three_fma(a0, a1, a2);
    double da = double(a);
    double de = double(e);
    double df = double(f);
    double da0 = double(a0);
    double da1 = double(a1);
    double da2 = double(a2);
    TTS_EQUAL(eve::fma(da0, da1, da2), (da+de+df));
  }
  else
  {
    using ld_t = long double;
    std::cout << sizeof(ld_t);
    auto [a, e, f] = three_fma(a0, a1, a2);
    ld_t da = ld_t(a);
    ld_t de = ld_t(e);
    ld_t df = ld_t(f);
    ld_t da0 = ld_t(a0);
    ld_t da1 = ld_t(a1);
    ld_t da2 = ld_t(a2);
    TTS_EQUAL(std::fmal(da0, da1, da2), (da+de+df));
  }
};
