//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::pow_abs return type")
{

  TTS_EXPR_IS(eve::pow_abs(EVE_TYPE(0)   , EVE_TYPE(0)  ), EVE_TYPE);
  TTS_EXPR_IS(eve::pow_abs(EVE_TYPE(0)   , EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pow_abs(EVE_VALUE(0) , EVE_TYPE(0)  ), EVE_TYPE);
}

TTS_CASE_TPL("Check eve::pow_abs behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pow_abs(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), T(0) );

    TTS_IEEE_EQUAL(eve::pow_abs(eve::inf(eve::as<T>()) , T(-0.5)       ), T(0)         );
    TTS_IEEE_EQUAL(eve::pow_abs(eve::inf(eve::as<T>()) , T( 0 )        ), T(1)         );
    TTS_IEEE_EQUAL(eve::pow_abs(eve::inf(eve::as<T>()) , T(0.5)        ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pow_abs(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));

    TTS_IEEE_EQUAL(eve::pow_abs(eve::nan(eve::as<T>()) ,  T(0)         ), T(1)         );
    TTS_IEEE_EQUAL(eve::pow_abs(eve::nan(eve::as<T>()) , -T(0)         ), T(1)         );
    TTS_IEEE_EQUAL(eve::pow_abs(eve::nan(eve::as<T>()) , eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(eve::pow_abs(T(0)  , T(-1)         ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pow_abs(T(0)  , T(-2)         ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pow_abs(T(0.5), eve::inf(eve::as<T>()) ), T(0)         );
    TTS_IEEE_EQUAL(eve::pow_abs(T(0.5), eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pow_abs(T(1)  , eve::nan(eve::as<T>()) ), T(1)         );
    TTS_IEEE_EQUAL(eve::pow_abs(T(1)  , eve::inf(eve::as<T>()) ), T(1)         );
    TTS_IEEE_EQUAL(eve::pow_abs(T(2)  , eve::minf(eve::as<T>())), T(0)         );
    TTS_IEEE_EQUAL(eve::pow_abs(T(2)  , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::pow_abs(T(-1)  , T(-1))  , T(1));
  TTS_IEEE_EQUAL(eve::pow_abs(T( 1)  , T( 1))  , T(1));
  TTS_IEEE_EQUAL(eve::pow_abs(T( 0)  , T( 0))  , T(1));
  TTS_IEEE_EQUAL(eve::pow_abs(T(-1)  , T( 5))  , T(1));
  TTS_IEEE_EQUAL(eve::pow_abs(T(-1)  , T( 6))  , T(1));
  TTS_ULP_EQUAL(eve::pow_abs(T(0.5) , T(0.25)), T(0.840896415253715)            , 2);
  TTS_ULP_EQUAL(eve::pow_abs(T(0.5) , T(0.25)), T(std::pow(EVE_VALUE(0.5), EVE_VALUE(0.25))), 2);

  if constexpr(!eve::scalar_value<T>)
  {
    using w8_t =  eve::wide<EVE_VALUE, eve::fixed<8>>;
    {
      w8_t a(0.25, 0.5, 1, 2.5, 100.0, 12.7, 4.0, 0.5);
      w8_t b(1.1, 2.2, 3.3, 4.4, 43.2, -0.7, 0.4, 0.0);
      TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(a, b) ,eve::pow_abs(a, b),2);
    }
    auto Nan =  eve::nan(eve::as<EVE_VALUE>());
    auto Inf =  eve::inf(eve::as<EVE_VALUE>());
    {
      w8_t a(2.4,  2.4, 1.0, 23.5, Nan,  12.5,  0.0,  0.0);
      w8_t b(0.0, -0.0, 2.4, 1.0,  12.5, Nan,  -3.0, -3.5);
      w8_t r(1.0,  1.0, 1.0, 23.5, Nan,  Nan,   Inf,  Inf);
      w8_t c = (eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      w8_t a( 0.0,  0.0,  0.0,  0.0,  0.0,   0.0, 1.0,  1.0);
      w8_t b(-4.0, -Inf, -Inf,  3.5,  3.0,   4.0, Inf,  -Inf);
      w8_t r( Inf,  Inf,  Inf,  0.0,  0.0,   0.0, 1.0,  1.0);
      w8_t c = (eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      w8_t a(2.0,  2.0,  Nan,  Inf, Inf,   1.0, 0.5, 1.5);
      w8_t b(0.0, -0.0,  0.0,  0.0,  0.0, -Inf, Inf, Inf);
      w8_t r(1.0,  1.0,  1.0,  1.0,  1.0,  1.0, 0.0, Inf);
      w8_t c = (eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      using w4_t =  eve::wide<EVE_VALUE, eve::fixed<4>>;
      w4_t a(  0.5,  1.5, Inf, Inf);
      w4_t b( -Inf, -Inf,-3.0, 3.0);
      w4_t r(  Inf,  0.0, 0.0, Inf );
      w4_t c = (eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
  }
}
