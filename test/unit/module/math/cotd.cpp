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
TTS_CASE_TPL( "Check return types of cotd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cotd(T())  , T);
  TTS_EXPR_IS( eve::cotd(v_t()), v_t);
};

//==================================================================================================
//== cotd  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of cotd on wide"
        , eve::test::simd::ieee_reals
        , tts::generate( tts::randoms(-45, 45)
                             , tts::randoms(-90, 90)
                             , tts::randoms(-5000,5000))
                             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::cotd;
  
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = eve::sind(e); return d ? eve::cosd(e)/eve::sind(e): eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cotd)(a0)  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cotd)(a0)     , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cotd)(a1)     , map(ref, a1), 40);
  TTS_ULP_EQUAL(eve::cotd(a0)                  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::cotd(a1)                  , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::cotd(a2)                  , map(ref, a2), 2);
};

TTS_CASE_TPL( "Check corner cases of cotd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using eve::cotd;
  TTS_ULP_EQUAL(cotd( T(  1))   , T(57.289961630759424687278147537112577980217522235144)    , 2);
  TTS_ULP_EQUAL(cotd(-T(  1))   , T(-57.289961630759424687278147537112577980217522235144)   , 2);
  TTS_ULP_EQUAL(cotd( T( 45))   , T(1)                                                      , 2);
  TTS_ULP_EQUAL(cotd(-T( 45))   , T(-1)                                                     , 2);
  TTS_ULP_EQUAL(cotd( T(500.0)) , T(-1.19175359259420995870530807186041933693070040770853)  , 2);
  TTS_ULP_EQUAL(cotd(-T(500.0)) , T(1.19175359259420995870530807186041933693070040770853)   , 2);



};
