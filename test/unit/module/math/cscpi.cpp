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
TTS_CASE_TPL("Check return types of cscpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cscpi(T()), T);
  TTS_EXPR_IS(eve::cscpi(v_t()), v_t);
};

//==================================================================================================
// cscpi  tests
//==================================================================================================
auto mmed = [](auto const& tgt)
{ return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };
auto med = [](auto const& tgt)
{ return eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };

TTS_CASE_WITH("Check behavior of cscpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.25, 0.25),
                            tts::randoms(-0.5, 0.5),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::cscpi;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t
  {
    auto d = eve::sinpi(double(e));
    return d ? 1.0 / d : eve::nan(eve::as(e));
  };

  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::quarter_circle(cscpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscpi)(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(cscpi(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(cscpi(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(cscpi(a2), map(ref, a2), 2);
  TTS_ULP_EQUAL(cscpi(a3), map(ref, a3), 2);
};
