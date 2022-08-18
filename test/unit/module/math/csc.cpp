//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of csc", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::csc(T()), T);
  TTS_EXPR_IS(eve::csc(v_t()), v_t);
};

//==================================================================================================
// csc  tests
//==================================================================================================
auto mquarter_c = []<typename T>(eve::as<T> const& tgt) { return -eve::pio_4(tgt); };
auto quarter_c  = []<typename T>(eve::as<T> const &tgt) { return eve::pio_4(tgt); };
auto mhalf_c    = []<typename T>(eve::as<T> const   &tgt) { return -eve::pio_2(tgt); };
auto half_c     = []<typename T>(eve::as<T> const    &tgt) { return eve::pio_2(tgt); };
auto mmed       = []<typename T>(eve::as<T> const      &tgt)
{ return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };
auto med = []<typename T>(eve::as<T> const& tgt)
{ return eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };

TTS_CASE_WITH("Check behavior of csc on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mquarter_c), tts::constant(quarter_c)),
                            tts::randoms(tts::constant(mhalf_c), tts::constant(half_c)),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::csc;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return 1.0 / std::sin(double(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(csc)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(csc)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(csc)(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(csc(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(csc(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(csc(a2), map(ref, a2), 2);
  TTS_ULP_EQUAL(csc(a3), map(ref, a3), 2);
};


//==================================================================================================
// Tests for masked csc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::csc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::csc[mask](a0),
            eve::if_else(mask, eve::csc(a0), a0));
};
