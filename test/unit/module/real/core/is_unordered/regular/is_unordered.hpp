//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_unordered.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check is_unordered return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_unordered(T(), T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_unordered behavior on arithmetic", EVE_TYPE)
{
  TTS_EQUAL(eve::is_unordered(T(1), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_unordered(T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), T(3)), eve::false_(eve::as<T>()));

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_unordered(eve::nan(eve::as<T>()) , T(3)          ), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_unordered(T(3)          , eve::nan(eve::as<T>()) ), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_unordered(eve::nan(eve::as<T>()) , eve::nan(eve::as<T>()) ), eve::true_(eve::as<T>()));
  }

  #if defined(EVE_SIMD_TESTS)
  T a = [](auto i,auto) { return i%2 ? eve::nan(eve::as_<EVE_VALUE>()) : 3;};
  T b = [](auto i,auto) { return i%3 ? 8 : eve::nan(eve::as_<EVE_VALUE>());};

  eve::logical<T> ref = [](auto i,auto)
  {
    EVE_VALUE u = i%2 ? eve::nan(eve::as_<EVE_VALUE>()) : 3;
    EVE_VALUE v = i%3 ? 8 : eve::nan(eve::as(u));
    return eve::is_unordered(u,v);
  };

  TTS_EQUAL(eve::is_unordered(a,b), ref );
  #endif
}
