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
TTS_CASE_TPL( "Check return types of cot"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cot(T())  , T);
  TTS_EXPR_IS( eve::cot(v_t()), v_t);
};

//==================================================================================================
// cot  tests
//==================================================================================================
auto mquarter_c = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto quarter_c  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto mhalf_c    = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto mfull_c    = []<typename T>(eve::as<T> const & tgt){  return -eve::pi(tgt);    };
auto full_c     = []<typename T>(eve::as<T> const & tgt){  return  eve::pi(tgt);    };
auto half_c     = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mmed       = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };
auto med        = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };

TTS_CASE_WITH ( "Check behavior of cot on wide"
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
  using eve::cot;
  
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return 1/std::tan(double(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cot)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cot)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cot)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(cot)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::full_circle(cot)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(cot)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(cot(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cot(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(cot(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(cot(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(cot(a4)                       , map(ref, a4), 2);
  

  TTS_IEEE_EQUAL(cot(T( 0 )), eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(cot(T(-0.)), eve::minf(eve::as<T>()));

};
