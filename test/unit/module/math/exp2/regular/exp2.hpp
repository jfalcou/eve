//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/minlog2denormal.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exp2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp2(T(0)), T);
}


TTS_CASE_TPL("Check eve::exp2 behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::exp2(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::exp2(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::exp2(T(4)), T(16));
  if constexpr(eve::signed_integral_value<T>)
  {
    TTS_IEEE_EQUAL(eve::exp2(T(-4)), T(0));
  }

  if constexpr(eve::floating_value<T>)
  {
    using elt_t =  eve::element_type_t<T>;
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::exp2(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::exp2(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::exp2(eve::minf(eve::as<T>())), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::exp2(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::exp2(T(-1)) , T(0.5), 0.5);
    TTS_ULP_EQUAL (eve::exp2(eve::minlog2(eve::as<T>())), T(0), 0.5);
    TTS_ULP_EQUAL (eve::exp2(eve::prev(eve::minlog2(eve::as<T>()))), T(0), 0.5);

    TTS_ULP_EQUAL (eve::exp2(eve::minlog2denormal(eve::as<T>())), T(std::exp2(eve::minlog2denormal(eve::as<elt_t>()))), 0.5);

  }
}

TTS_CASE_TPL("Check float64 & float32(eve::exp2) behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    if constexpr(eve::scalar_value<T> )
    {
      TTS_EXPR_IS(eve::float64(eve::exp2)(T(0)), double);
      TTS_EXPR_IS(eve::float32(eve::exp2)(T(0)), float);
      TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(37)), exp2(float(37)));
      TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(126)), exp2(float(126)));
      if constexpr(sizeof(v_t) > 1 || std::is_unsigned_v<v_t>)
      {
        TTS_IEEE_EQUAL(eve::float32(eve::exp2)(eve::next(T(127))), eve::inf(eve::as<float>()));
        TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(129)), eve::inf(eve::as<float>()));
      }


      TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(37)), exp2(double(37)));
      TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(127)), exp2(double(127)));
      if constexpr(sizeof(v_t) > 1)
      {
        TTS_IEEE_EQUAL(eve::float64(eve::exp2)(eve::next(T(1023))), eve::inf(eve::as<double>()));
        TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(1025)), eve::inf(eve::as<double>()));
      }
    }
    else
    {
      using d_t = eve::wide<double, eve::cardinal_t<T>>;
      using f_t = eve::wide<float, eve::cardinal_t<T>>;
      TTS_EXPR_IS(eve::float64(eve::exp2)(T(0)), d_t);
      TTS_EXPR_IS(eve::float32(eve::exp2)(T(0)), f_t);
      TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(37)), eve::exp2(f_t(37)));
      TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(126)), eve::exp2(f_t(126)));
      if constexpr(sizeof(v_t) > 1 || std::is_unsigned_v<v_t>)
      {
        TTS_IEEE_EQUAL(eve::float32(eve::exp2)(eve::next(T(127))), eve::inf(eve::as<f_t>()));
        TTS_IEEE_EQUAL(eve::float32(eve::exp2)(T(129)), eve::inf(eve::as<f_t>()));
      }


      TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(37)), eve::exp2(d_t(37)));
      TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(127)),eve::exp2(d_t(127)));
      if constexpr(sizeof(v_t) > 1)
      {
        TTS_IEEE_EQUAL(eve::float64(eve::exp2)(eve::next(T(1023))), eve::inf(eve::as<d_t>()));
        TTS_IEEE_EQUAL(eve::float64(eve::exp2)(T(1025)), eve::inf(eve::as<d_t>()));
      }

    }

  }
  else
    TTS_EQUAL(0, 0);

}
