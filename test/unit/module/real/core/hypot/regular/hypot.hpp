//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check hypot return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::hypot(   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::hypot( v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::hypot(   T(0), v_t(0)), T);

  TTS_EXPR_IS(eve::hypot(   T(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::hypot(   T(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::hypot(   T(0), v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::hypot(   T(0), v_t(0), v_t(0)), T);
  TTS_EXPR_IS(eve::hypot( v_t(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::hypot( v_t(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::hypot( v_t(0), v_t(0),   T(0)), T);
}

TTS_CASE_TPL("Check eve::hypot behavior", EVE_TYPE)
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::hypot(eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::hypot(eve::inf(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::hypot(eve::valmax(eve::as<T>()) , T(0)            ) , eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::hypot(T(0)             , eve::valmax(eve::as<T>())) , eve::inf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::hypot(T(-1), T(-1))                      , eve::sqrt_2(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::hypot(T( 1), T( 1))                      , eve::sqrt_2(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::hypot(T( 0), T( 0))                      , T(0)            , 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::sqrt_2(eve::as<T>()), eve::sqrt_2(eve::as<T>())), T(2)            , 0.5);
}

TTS_CASE_TPL("Check 3 params eve::hypot behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::hypot(eve::nan(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::hypot(eve::inf(eve::as<T>()), eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::hypot(eve::valmax(eve::as<T>()) , T(0)            , T(0)) , eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::hypot(T(0)             , eve::valmax(eve::as<T>()), T(0)) , eve::inf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::hypot(T(-1), T(-1), eve::sqrt_2(eve::as<T>()) ) , T(2)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(T( 1), T( 1), eve::sqrt_2(eve::as<T>()) ) , T(2)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(T( 0), T( 0), T( 0)            ) , T(0)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(T( 1), T( 1), T( 1)            ) , T(std::sqrt(v_t(3))), 0.5);
}
