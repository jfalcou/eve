//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::convert) return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint64_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint64_t;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<std::uint64_t>()), target_t);
}

TTS_CASE_TPL("Check eve::saturated(eve::convert) behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint64_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint64_t;
#endif

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<std::uint64_t>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(0))          , eve::as<std::uint64_t>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69))      , eve::as<std::uint64_t>()), static_cast<target_t>(v_t(42.69)) );

  if constexpr(eve::integral_value<T>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<std::uint64_t>()), static_cast<target_t>(eve::valmax(eve::as<v_t>())) );
  }
}
