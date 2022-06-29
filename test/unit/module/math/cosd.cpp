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
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
// //==================================================================================================
// TTS_CASE_TPL( "Check return types of cosd"
//             , eve::test::simd::ieee_reals
//             )
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;

//   TTS_EXPR_IS( eve::cosd(T())  , T);
//   TTS_EXPR_IS( eve::cosd(v_t()), v_t);
// };

//==================================================================================================
//== cosd  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of cosd on wide"
        , eve::test::simd::ieee_reals
        , tts::generate( tts::randoms(-45 ,45)
                             , tts::randoms(-90, 90)
                             , tts::randoms(-5000, 5000))
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::cosd;
  
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return boost::math::cos_pi(e/180.0l); };

  TTS_ULP_EQUAL(eve::quarter_circle(cosd)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cosd)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cosd)(a1)           , map(ref, a1), 30);
  TTS_ULP_EQUAL(cosd(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cosd(a1)                       , map(ref, a1), 30);
  TTS_ULP_EQUAL(cosd(a2)                       , map(ref, a2), 420);
};

TTS_CASE_TPL( "Check return types of cosd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  TTS_ULP_EQUAL(eve::cosd(T(1))      , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::cosd(T(-1))     , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::cosd(T(45.0))   , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::cosd(-T(45.0))  , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::cosd(T(-500.0)) , T(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
  TTS_ULP_EQUAL(eve::cosd(T(500.0))  , T(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
//   using v_t = eve::element_type_t<T>;
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
// //    TTS_ULP_EQUAL(eve::cosd(T(-89.9948004))  , T(9.0750139662133702308589680368087310425111681700988e-5l)   , 3.5 );
//     T x(-3870.0014720); //-87.2292316); ///*(-89.9948004); /*/(+24.2768812);
//     TTS_ULP_EQUAL(eve::cosd(x), map([](auto e) -> v_t { return boost::math::cos_pi(((long double)e)/180.0l); }, x), 2);
//     TTS_ULP_EQUAL(eve::cospi(x),  T(2.5691246586530322324691158981079804836564072146655e-5), 2);
//   }
//   else TTS_PASS("***");
// //   eve::wide < v_t, eve::fixed < 4>> u{-3870.0014720, +856.9305370, -1459.2691069, +11.4976682};
// //     TTS_ULP_EQUAL(eve::cosd(u), map([](auto e) -> v_t { return boost::math::cos_pi(((long double)e)/180.0l); }, u), 2);

};
