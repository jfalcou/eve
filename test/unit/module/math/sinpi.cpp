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
TTS_CASE_TPL("Check return types of sinpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinpi(T()), T);
  TTS_EXPR_IS(eve::sinpi(v_t()), v_t);
};

//==================================================================================================
// sinpi  tests
//==================================================================================================
auto mmed = [](auto const& tgt)
{ return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };
auto med = [](auto const& tgt)
{ return eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };

TTS_CASE_WITH("Check behavior of sinpi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.25, 0.25),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::sinpi;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;
  long double  pi = 3.1415926535897932384626433832795028841971693993751l;
  auto ref  = [pi](auto e) -> v_t { return std::sin((pi*(long double)e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(sinpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sinpi)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sinpi(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sinpi(a1), sinpi(eve::frac(a1)+eve::binarize(eve::is_odd(eve::trunc(a1)))), 2);
  TTS_ULP_EQUAL(sinpi(a2), sinpi(eve::frac(a2)+eve::binarize(eve::is_odd(eve::trunc(a2)))), 2);
};


//==================================================================================================
// Tests for masked sinpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sinpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sinpi[mask](a0),
            eve::if_else(mask, eve::sinpi(a0), a0));
};
