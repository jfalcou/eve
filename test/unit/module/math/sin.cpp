//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
TTS_CASE_TPL( "Check return types of sin"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sin(T())  , T);
  TTS_EXPR_IS( eve::sin(v_t()), v_t);
};

//==================================================================================================
// sin  tests
//==================================================================================================
auto mquarter_c = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto quarter_c  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto mhalf_c    = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto half_c     = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mfull_c    = []<typename T>(eve::as<T> const & tgt){  return -eve::pi(tgt);    };
auto full_c     = []<typename T>(eve::as<T> const & tgt){  return  eve::pi(tgt);    };
auto mmed       = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };
auto med        = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };

TTS_CASE_WITH ( "Check behavior of sin on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(tts::constant(mquarter_c), tts::constant(quarter_c))
                              , tts::randoms(tts::constant(mhalf_c)   , tts::constant(half_c))
                              , tts::randoms(tts::constant(mfull_c)   , tts::constant(full_c))
                              , tts::randoms(tts::constant(mmed)      , tts::constant(med))
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4)
{
  using eve::detail::map;
  using eve::sin;

  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return std::sin(e); };
  TTS_ULP_EQUAL(eve::quarter_circle(sin)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sin)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sin)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(sin(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sin(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(sin(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(sin(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(sin(a4)                       , map(ref, a4), 2);

};
