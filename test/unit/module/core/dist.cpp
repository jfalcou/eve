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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of dist", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::dist(T(), T()), T);
  TTS_EXPR_IS(eve::dist(T(), v_t()), T);
  TTS_EXPR_IS(eve::dist(v_t(), T()), T);
  TTS_EXPR_IS(eve::dist(T(), int()), T);
  TTS_EXPR_IS(eve::dist(int(), T()), T);
  TTS_EXPR_IS(eve::dist(v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::saturated(eve::dist)(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::dist)(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::dist)(v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::dist)(T(), int()), T);
  TTS_EXPR_IS(eve::saturated(eve::dist)(int(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::dist)(v_t(), v_t()), v_t);
};

//==================================================================================================
//== dist tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of dist(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a0, T a1)
{
  using eve::dist;
  using eve::detail::map;
  TTS_ULP_EQUAL(dist(a0, a1), eve::max(a0, a1) - eve::min(a0, a1), 2);
  TTS_ULP_EQUAL(eve::saturated(dist)(a0, a1), [](auto a, auto b){
                  auto d = eve::dist(a, b);
                  if constexpr(eve::unsigned_value<T>) return d;
                  else  return eve::if_else(eve::is_ltz(d),  eve::valmax(eve::as<T>()),  d);
                }(a0, a1), 2);
};
