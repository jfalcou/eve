//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of powm1"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::powm1(T(), T())  , T);
  TTS_EXPR_IS( eve::powm1(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::powm1(T(), v_t()), T);
};

//==================================================================================================
// powm1  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of powm1 on wide"
        , eve::test::simd::ieee_reals
        , tts::generate( tts::randoms(0, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(1.0, 10.0)
                             , tts::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_RELATIVE_EQUAL(eve::powm1(a0, a1)      , map([](auto e, auto f) -> v_t { return eve::pow(double(e), double(f))-1; }, a0, a1), 0.001);
  TTS_RELATIVE_EQUAL(eve::powm1(a2, a3)      , map([](auto e, auto f) -> v_t { return eve::pow(double(e), double(f))-1; }, a2, a3), 0.001);




};


TTS_CASE_TPL( "Check  powm1"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using eve::dec;
  TTS_IEEE_EQUAL(eve::powm1( T(0)          ,  T(-1)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1(-T(0)          ,  T(-1)          )          , eve::minf(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::powm1(-T(0)          ,  T(-2)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1( T(0)          ,  T(-2)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1( T(0)          ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1(-T(0)          ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1(-T(1)          ,  eve::minf(eve::as<T>()) ) , T(0)          );
  TTS_IEEE_EQUAL(eve::powm1(-T(1)          ,  eve::inf(eve::as<T>())  ) , T(0)          );
  TTS_IEEE_EQUAL(eve::powm1( T(1)          ,  eve::nan(eve::as<T>())  ) , T(0)          );
  TTS_IEEE_EQUAL(eve::powm1( eve::nan(eve::as<T>()) ,  T(0)           ) , T(0)          );
  TTS_IEEE_EQUAL(eve::powm1( eve::nan(eve::as<T>()) , -T(0)           ) , T(0)          );
  TTS_IEEE_EQUAL(eve::powm1( T(0.5)        ,  eve::inf(eve::as<T>())  ) , T(-1 )        );
  TTS_IEEE_EQUAL(eve::powm1( T(2)          ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1( T(0.5)        ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1( T(2)          ,  eve::minf(eve::as<T>()) ) , T(-1 )        );
  TTS_IEEE_EQUAL(eve::powm1(-T(0.5)        ,  eve::inf(eve::as<T>())  ) , T(-1 )        );
  TTS_IEEE_EQUAL(eve::powm1(-T(2)          ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1(-T(0.5)        ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1(-T(2)          ,  eve::minf(eve::as<T>()) ) , T(-1)        );
  TTS_IEEE_EQUAL(eve::powm1( eve::minf(eve::as<T>()), -T(3)           ) , T(-1)        );
  TTS_IEEE_EQUAL(eve::powm1( eve::minf(eve::as<T>()), -T(4)           ) , T(-1)        );
  TTS_IEEE_EQUAL(eve::powm1( eve::inf(eve::as<T>()) ,  T(4)           ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::powm1( eve::inf(eve::as<T>()) , -T(4)           ) , T( -1)        );

  using v_t =  eve::element_type_t<T>;
  using w8_t =  eve::wide<v_t, eve::fixed<8>>;
  auto Inf =  eve::inf(eve::as<v_t>());
  {
    w8_t a(-0.0, -0.0,-0.0,-0.0,-1.0,-1.0, -Inf, -Inf);
    w8_t b(-Inf, -3.0,-4.0,-4.5,-Inf, Inf, -3.0, -4.0);
    w8_t r( Inf, -Inf, Inf, Inf, 1.0, 1.0, -0.0,  0.0);
    w8_t c = (eve::powm1)(a, b);
    TTS_ULP_EQUAL(c ,dec(r),2);
  }
  {
    using w4_t =  eve::wide<v_t, eve::fixed<4>>;
    w4_t a(-Inf, -Inf, -Inf, 0.0);
    w4_t b(-4.5,  4.0,  4.5, 0.0);
    w4_t r( 0.0,  Inf,  Inf, 1.0);
    w4_t c = (eve::powm1)(a, b);
    TTS_ULP_EQUAL(c ,dec(r),2);
  }
};
