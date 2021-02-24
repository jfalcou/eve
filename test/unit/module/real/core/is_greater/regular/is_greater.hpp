//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_greater.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_greater return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::is_greater(  T() ,   T() ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_greater(  T() , v_t() ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_greater(v_t() ,   T() ), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_greater behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_greater(T(1), eve::nan(eve::as<T>())), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_greater(eve::nan(eve::as<T>()), T(1)), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_greater(T(1)  , T(1)  ), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_greater(T(1)  , v_t(1)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_greater(v_t(1), T(1)  ), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_greater(T(3)  , T(1)  ), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_greater(T(3)  , v_t(1)), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_greater(v_t(3), T(1)  ), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_greater(T(1)  , T(3)  ), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_greater(T(1)  , v_t(3)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_greater(v_t(1), T(3)  ), eve::false_(eve::as<T>()) );
}
