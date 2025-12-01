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
//== three_fma scalar tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of three_fma)",
              eve::test::scalar::ieee_reals_wf16,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)
                           )
             )
<typename T>(T a0, T a1, T a2)
{
  using eve::three_fma;
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 2)
  {
    using u_t = float;
    auto [a, e, f] = three_fma(a0, a1, a2);
    u_t da = u_t(a);
    u_t de = u_t(e);
    u_t df = u_t(f);
    u_t da0 = u_t(a0);
    u_t da1 = u_t(a1);
    u_t da2 = u_t(a2);
    auto dn = [](auto z){return eve::convert(z, eve::as<eve::float16_t>());};
    TTS_IEEE_EQUAL(dn(eve::fma[eve::pedantic](da0, da1, da2)), dn(da+de+df));
  }
   else  if constexpr(sizeof(e_t) ==  4)
  {
    using u_t = eve::upgrade_t<e_t>;
    auto [a, e, f] = three_fma(a0, a1, a2);
    u_t da = u_t(a);
    u_t de = u_t(e);
    u_t df = u_t(f);
    u_t da0 = u_t(a0);
    u_t da1 = u_t(a1);
    u_t da2 = u_t(a2);
    std::cout << tts::typename_<T> << std::endl;
    TTS_IEEE_EQUAL(eve::downgrade(eve::fma[eve::pedantic](da0, da1, da2)), eve::downgrade(da+de+df));
  }
  else
  {
    using ld_t = long double;
    std::cout << sizeof(ld_t);
    auto [a, e, f] = three_fma(a0, a1, a2);
    ld_t da = ld_t(double(a));
    ld_t de = ld_t(double(e));
    ld_t df = ld_t(double(f));
    ld_t da0 = ld_t(double(a0));
    ld_t da1 = ld_t(double(a1));
    ld_t da2 = ld_t(double(a2));
    TTS_EQUAL(double(std::fmal(da0, da1, da2)), double(da+de+df));
  }
};
