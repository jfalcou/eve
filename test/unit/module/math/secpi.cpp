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
//==================================================================================================
TTS_CASE_TPL( "Check return types of secpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::secpi(T())  , T);
  TTS_EXPR_IS( eve::secpi(v_t()), v_t);
};

//==================================================================================================
// secpi  tests
//==================================================================================================
auto mmed = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };
auto med  = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };

TTS_CASE_WITH ( "Check behavior of secpi on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(-0.25, 0.25)
                              , tts::randoms(-0.5 , 0.5)
                              , tts::randoms(tts::constant(mmed), tts::constant(med))
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::secpi;

  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto c = boost::math::cos_pi(e); return c ? 1.0/boost::math::cos_pi(e) : eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(secpi)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(secpi)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(secpi)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(secpi(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(secpi(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(secpi(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(secpi(a3)                       , map(ref, a3), 2);




};
