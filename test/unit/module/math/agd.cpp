//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of agd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::agd(T()), T);
  TTS_EXPR_IS(eve::agd(v_t()), v_t);
};

//==================================================================================================
// agd  tests
//==================================================================================================
auto maxi = ::tts::constant([]<typename T>(eve::as<T> const& tgt) { return eve::pio_2(tgt); });
auto mini = ::tts::constant([]<typename T>(eve::as<T> const& tgt) { return -eve::pio_2(tgt); });

TTS_CASE_WITH("Check behavior of agd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi), tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::agd;
  TTS_ULP_EQUAL(agd(a0), map([](auto e) -> v_t { return 2*std::atanh(std::tan(e*eve::half(eve::as(e)))); }, a0), 2.0);
  TTS_ULP_EQUAL(agd(a1), map([](auto e) -> v_t { return 2*std::atanh(std::tan(e*eve::half(eve::as(e)))); }, a1), 2.0);
};


//==================================================================================================
// Tests for masked agd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::agd)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::agd[mask](a0),
            eve::if_else(mask, eve::agd(a0), a0));
};
