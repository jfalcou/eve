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
TTS_CASE_TPL("Check return types of sinc", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinc(T()), T);
  TTS_EXPR_IS(eve::sinc(v_t()), v_t);
};

//==================================================================================================
// sinc  tests
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return eve::next(eve::mindenormal(tgt)); });
auto maxi = tts::constant([](auto tgt) { return eve::valmax(tgt) / 2; });

TTS_CASE_WITH("Check behavior of sinc on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi), tts::randoms(-10.0, 10.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::sinc;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;

  auto ref = [](auto e) -> v_t { return e ? std::sin(e) / e : v_t(1); };
  TTS_ULP_EQUAL(sinc(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sinc(a1), map(ref, a1), 2);
};


//==================================================================================================
// Tests for masked sinc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sinc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sinc[mask](a0),
            eve::if_else(mask, eve::sinc(a0), a0));
};
