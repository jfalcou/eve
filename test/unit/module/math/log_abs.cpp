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
TTS_CASE_TPL("Check return types of log_abs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::log_abs(T()), T);
  TTS_EXPR_IS(eve::log_abs(v_t()), v_t);
};

//==================================================================================================
// log_abs  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of log_abs on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1, 1)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::log_abs(a0), map([](auto e) -> v_t { return std::log(std::abs(e)); }, a0), 2);
};
