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
TTS_CASE_TPL("Check return types of sigmoid", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sigmoid(T()), T);
  TTS_EXPR_IS(eve::sigmoid(v_t()), v_t);
};

//==================================================================================================
// exp  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of exp on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog), tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::sigmoid(a0), map([](auto e) -> v_t { return eve::rec(eve::inc(std::exp(-e))); }, a0), 2);
  TTS_ULP_EQUAL(eve::sigmoid(a1), map([](auto e) -> v_t { return eve::rec(eve::inc(std::exp(-e))); }, a1), 2);
};


TTS_CASE_TPL("Check return types of sigmoid", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
   TTS_IEEE_EQUAL(eve::sigmoid(T(0.)), T(0.5));
  TTS_IEEE_EQUAL(eve::sigmoid(T(-0.)), T(0.5));

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sigmoid(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::sigmoid(eve::inf(eve::as<T>())), eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::sigmoid(eve::minf(eve::as<T>())), T(0));
  }
};


//==================================================================================================
//   Tests for masked sigmoid
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sigmoid)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sigmoid[mask](a0), eve::if_else(mask, eve::sigmoid(a0), a0));
};
