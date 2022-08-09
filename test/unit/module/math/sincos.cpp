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
TTS_CASE_TPL( "Check return types of cos"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sincos(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::sincos(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto quarter_c   = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto mhalf_c = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto half_c  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mfull_c =[]<typename T>(eve::as<T> const & tgt){  return -eve::pi(tgt);    };
auto full_c =[]<typename T>(eve::as<T> const & tgt){  return  eve::pi(tgt);    };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };

TTS_CASE_WITH ( "Check behavior of cos on wide"
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
  using eve::sincos;

  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return std::cos(e); };
  auto refs = [](auto e) -> v_t { return std::sin(e); };
  {
    auto [s, c] = eve::quarter_circle(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
  }
  {
    auto [s, c] = eve::half_circle(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::half_circle(sincos)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
  }
  {
    auto [s, c] = eve::full_circle(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::full_circle(sincos)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = eve::full_circle(sincos)(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
  }
  {
    auto [s, c] = sincos(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = sincos(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = sincos(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
    auto [s3, c3] = sincos(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
    auto [s4, c4] = sincos(a4);
    TTS_ULP_EQUAL(s4      , map(refs, a4), 2);
    TTS_ULP_EQUAL(c4      , map(refc, a4), 2);
  }
};
