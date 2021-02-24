//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/pow_abs.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::pedantic(eve::pow_abs) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic(eve::pow_abs)(T(0)   , T(0)  ), T);
  TTS_EXPR_IS(eve::pedantic(eve::pow_abs)(T(0)   , v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::pow_abs)(v_t(0) , T(0)  ), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::pow_abs) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
   if constexpr(eve::platform::supports_invalids)
   {
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), T(0) );

     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(eve::inf(eve::as<T>()) , T(-0.5)       ), T(0)         );
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(eve::inf(eve::as<T>()) , T(0.5)        ), eve::inf(eve::as<T>()));
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));

     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(eve::nan(eve::as<T>()) , eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));

     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(2)  , eve::minf(eve::as<T>())), T(0)         );
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(2)  , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));

     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(0)  , T(-1)         ), eve::inf(eve::as<T>()));
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(0)  , T(-2)         ), eve::inf(eve::as<T>()));
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5), eve::inf(eve::as<T>()) ), T(0)         );
     TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5), eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));
    }

   TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(-1)  , T(-1))  , T(1));
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T( 2)  , T( 1.5))  , eve::pow_abs(T(2), T(1.5)), 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T( 10.5) , T( 4.5))  , eve::pow_abs(T( 10.5) , T( 4.5)), 2);
   TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(-1)  , T( 5))  , T(1));
   TTS_IEEE_EQUAL(eve::pedantic(eve::pow_abs)(T(-1)  , T( 6))  , T(1));
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5) , T(0.25)), T(0.840896415253715)            , 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5) , T(0.25)), T(std::pow(v_t(0.5), v_t(0.25))), 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5) , T(2.5)), T(std::pow(v_t(0.5), v_t(2.5))), 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(1.5) , T(1.0e19)), T(eve::inf(eve::as<T>())), 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(0.5) , T(1.0e19)), T(0), 2);
   TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(T(10.0), T(10.0)), T(10000000000.0), 2);

   if constexpr(!eve::real_scalar_value<T>)
  {
    using w8_t =  eve::wide<v_t, eve::fixed<8>>;
    {
      w8_t a(0.25, 0.5, 1, 2.5, 100.0, 12.7, 4.0, 0.5);
      w8_t b(1.1, 2.2, 3.3, 4.4, 43.2, -0.7, 0.4, 0.0);
      TTS_ULP_EQUAL(eve::pedantic(eve::pow_abs)(a, b) ,eve::pow_abs(a, b),2);
    }
    auto Nan =  eve::nan(eve::as<v_t>());
    auto Inf =  eve::inf(eve::as<v_t>());
    {
      w8_t a(2.4,  2.4, 1.0, 23.5, Nan,  12.5,  0.0,  0.0);
      w8_t b(0.0, -0.0, 2.4, 1.0,  12.5, Nan,  -3.0, -3.5);
      w8_t r(1.0,  1.0, 1.0, 23.5, Nan,  Nan,   Inf,  Inf);
      w8_t c = eve::pedantic(eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      w8_t a( 0.0,  0.0,  0.0,  0.0,  0.0,   0.0, 1.0,  1.0);
      w8_t b(-4.0, -Inf, -Inf,  3.5,  3.0,   4.0, Inf,  -Inf);
      w8_t r( Inf,  Inf,  Inf,  0.0,  0.0,   0.0, 1.0,  1.0);
      w8_t c = eve::pedantic(eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      w8_t a(2.0,  2.0,  Nan,  Inf, Inf,   1.0, 0.5, 1.5);
      w8_t b(0.0, -0.0,  0.0,  0.0,  0.0, -Inf, Inf, Inf);
      w8_t r(1.0,  1.0,  1.0,  1.0,  1.0,  1.0, 0.0, Inf);
      w8_t c = eve::pedantic(eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
    {
      using w4_t =  eve::wide<v_t, eve::fixed<4>>;
      w4_t a(  0.5,  1.5, Inf, Inf);
      w4_t b( -Inf, -Inf,-3.0, 3.0);
      w4_t r(  Inf,  0.0, 0.0, Inf );
      w4_t c = eve::pedantic(eve::pow_abs)(a, b);
      TTS_ULP_EQUAL(c ,r,2);
    }
  }
}
