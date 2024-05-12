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
TTS_CASE_TPL("Check return types of tanpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::tanpi(T()), T);
  TTS_EXPR_IS(eve::tanpi(v_t()), v_t);
};

//==================================================================================================
// tanpi  tests
//==================================================================================================
auto mmed = []<typename T>(eve::as<T> const& tgt)
{ return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };
auto med = []<typename T>(eve::as<T> const& tgt)
{ return eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };

TTS_CASE_WITH("Check behavior of tanpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.25, 0.25),
                            tts::randoms(-0.5, 0.5),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::tanpi;
  using eve::detail::map;

  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t
  {
    auto d = eve::cospi(e);
    return d ? eve::sinpi(e) / d : eve::nan(eve::as(e));
  };
  TTS_ULP_EQUAL(eve::quarter_circle(tanpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tanpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tanpi)(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(tanpi(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(tanpi(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(tanpi(a2), map(ref, a2), 2);
  TTS_ULP_EQUAL(tanpi(a3), map(ref, a3), 2);
};


//==================================================================================================
// Tests for masked tanpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::tanpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::tanpi[mask](a0),
            eve::if_else(mask, eve::tanpi(a0), a0));
};
