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
TTS_CASE_TPL("Check return types of nb_values", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;

  // regular
  TTS_EXPR_IS(eve::nb_values(T(), T()), ui_t);
  TTS_EXPR_IS(eve::nb_values(T(), v_t()), ui_t);
  TTS_EXPR_IS(eve::nb_values(v_t(), T()), ui_t);
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::nb_values(T(), int()), ui_t);
    TTS_EXPR_IS(eve::nb_values(int(), T()), ui_t);
  }
  TTS_EXPR_IS(eve::nb_values(v_t(), v_t()), vi_t);
};

//==================================================================================================
//== nb_values tests
//==================================================================================================
TTS_CASE_TPL("Check return types of nb_values", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using ui_t = eve::as_integer_t<T, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      auto vm = eve::valmax(eve::as<ui_t>());
      auto vz = eve::zero(eve::as<ui_t>());
      TTS_EQUAL(eve::nb_values(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), vz);
      TTS_EQUAL(eve::nb_values(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())),vz);
      TTS_EQUAL(eve::nb_values(eve::nan(eve::as<T>()), eve::minf(eve::as<T>())),vm);
    }

    TTS_EQUAL(eve::nb_values(T(-1), T(-1)), ui_t(0));
  }
  else
  {
    TTS_EQUAL(eve::nb_values(T(2), T(0)), ui_t(2));
  }


};
