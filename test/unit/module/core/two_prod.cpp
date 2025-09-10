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
TTS_CASE_WITH("Check behavior of average(wide)",
              eve::test::scalar::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1)
{
  using eve::two_prod;
  if constexpr(sizeof(eve::element_type_t<T>) == 4)
  {
    auto [a, e] = two_prod(a0, a1);
    double da = double(a);
    double de = double(e);
    double da0 = double(a0);
    double da1 = double(a1);
    TTS_EQUAL(da0*da1, (da+de));
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
    TTS_EQUAL(da0*da1, (da+de));
  }
};
