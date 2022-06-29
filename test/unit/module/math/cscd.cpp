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
TTS_CASE_TPL( "Check return types of cscd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cscd(T())  , T);
  TTS_EXPR_IS( eve::cscd(v_t()), v_t);
};

//==================================================================================================
// cscd  tests
//==================================================================================================
TTS_CASE_WITH ( "Check behavior of cscd on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(-45, 45)
                              , tts::randoms(-90,90)
                              , tts::randoms(-5000,5000)
                              )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::cscd;

  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = eve::sind(e);return d ? 1.0/d : eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cscd)(a0)  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscd)(a0)     , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscd)(a1)     , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::cscd(a0)                  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::cscd(a1)                  , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::cscd(a2)                  , map(ref, a2), 2);
};
