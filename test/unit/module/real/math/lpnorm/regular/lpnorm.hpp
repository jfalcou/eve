//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lpnorm.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check lpnorm return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::lpnorm(2,     T(0),   T(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,   v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,     T(0), v_t(0)), T);

  TTS_EXPR_IS(eve::lpnorm(2,     T(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,     T(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,     T(0), v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,     T(0), v_t(0), v_t(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,   v_t(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,   v_t(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::lpnorm(2,   v_t(0), v_t(0),   T(0)), T);
}

TTS_CASE_TPL("Check eve::lpnorm behavior", EVE_TYPE)
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::lpnorm(2,  eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::lpnorm(2,  eve::inf(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::lpnorm(2,  eve::valmax(eve::as<T>()) , T(0)            ) , eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::lpnorm(2,  T(0)             , eve::valmax(eve::as<T>())) , eve::inf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::lpnorm(2,  T(-1), T(-1))                      , eve::sqrt_2(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(2,  T( 1), T( 1))                      , eve::sqrt_2(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(2,  T( 0), T( 0))                      , T(0)            , 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(2,  eve::sqrt_2(eve::as<T>()), eve::sqrt_2(eve::as<T>())), T(2)            , 0.5);
}

TTS_CASE_TPL("Check 3 params eve::lpnorm p = 3 behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::lpnorm(3,  eve::nan(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::lpnorm(3,  eve::inf(eve::as<T>()), eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::lpnorm(3,  eve::valmax(eve::as<T>()) , T(0)            , T(0)) , eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::lpnorm(3,  T(0)             , eve::valmax(eve::as<T>()), T(0)) , eve::inf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::lpnorm(3,  T(-1), T(-1), T(-1) ) , T(eve::nthroot(3.0, 3.0))                , 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(3,  T( 0), T( 0), T( 0)            ) , T(0)                , 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(3,  T( 1), T( 1), T( 1)            ) , T(eve::nthroot(v_t(3), 3)), 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(3,  T( 4), T( 3)                   ) , T(4.497941445275415), 0.5);
}

TTS_CASE_TPL("Check 3 params eve::lpnorm p = 3 wide behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::lpnorm(T(3),  eve::nan(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::lpnorm(T(3),  eve::inf(eve::as<T>()), eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::lpnorm(T(3),  eve::valmax(eve::as<T>()) , T(0)            , T(0)) , eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::lpnorm(T(3),  T(0)             , eve::valmax(eve::as<T>()), T(0)) , eve::inf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::lpnorm(T(3),  T(-1), T(-1), T(-1)            ) , T(eve::nthroot(3.0, 3.0))    , 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(T(3),  T( 0), T( 0), T( 0)            ) , T(0)                , 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(T(3),  T( 1), T( 1), T( 1)            ) , T(eve::nthroot(v_t(3), 3)), 0.5);
  TTS_ULP_EQUAL(eve::lpnorm(T(3),  T( 4), T( 3)                   ) , T(4.497941445275415), 0.5);
}
