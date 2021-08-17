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
#include <type_traits>

TTS_CASE_TPL("Check eve::convert return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<double, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = double;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<double>()), target_t);
}

TTS_CASE_TPL("Check eve::convert behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<double, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = double;
#endif

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<double>()), static_cast<target_t>(eve::valmin(eve::as<v_t>())) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(0))          , eve::as<double>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69))      , eve::as<double>()), static_cast<target_t>(v_t(42.69)) );
  TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<double>()), static_cast<target_t>(eve::valmax(eve::as<v_t>())) );
}
