//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturated/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::convert) return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<float>()), target_t);
}

TTS_CASE_TPL("Check eve::saturated(eve::convert) behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  using v_t = eve::element_type_t<T>;

  if constexpr(std::is_same_v<v_t, double>)
  {
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<float>()), (eve::valmin(eve::as<target_t>())) );
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<float>()), (eve::valmax(eve::as<target_t>())) );
  }
  else
  {
    if constexpr(sizeof(v_t)<=sizeof(float))
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<float>()), static_cast<target_t>(eve::valmin(eve::as<v_t>())) );
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<float>()), static_cast<target_t>(eve::valmax(eve::as<v_t>())) );
    }
  }

  TTS_EQUAL(eve::saturated(eve::convert)((T(0))          , eve::as<float>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69))      , eve::as<float>()), static_cast<target_t>(v_t(42.69)) );
}
