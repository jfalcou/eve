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
TTS_CASE_TPL("Check return types of sinhc", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinhc(T()), T);
  TTS_EXPR_IS(eve::sinhc(v_t()), v_t);
};

//==================================================================================================
// sinhc  tests
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T> const& tgt) { return -eve::maxlog(tgt); });

TTS_CASE_WITH("Check behavior of sinhc on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, eve::maxlog), tts::randoms(-10.0, 10.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::sinhc;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return e ? std::sinh(e) / e : v_t(1); };
  TTS_ULP_EQUAL(sinhc(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sinhc(a1), map(ref, a1), 2);
};


//==================================================================================================
// Tests for masked sinhc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sinhc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sinhc[mask](a0),
            eve::if_else(mask, eve::sinhc(a0), a0));
};
