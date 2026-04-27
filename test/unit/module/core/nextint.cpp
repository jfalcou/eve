//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/eve.hpp>

//==================================================================================================
//= Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::nextint", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::nextint(T{}), T);
  TTS_EXPR_IS(eve::nextint(v_t{}), v_t);
};

//==================================================================================================
//= Tests for eve::nextint
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::nextint(eve::wide)",
              eve::test::simd::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a0)
{
  if constexpr (eve::integral_value<T>)
  {
    TTS_EQUAL(eve::nextint(a0), eve::inc(a0));
  }
  else
  {
    using v_t = eve::element_type_t<T>;
    TTS_EQUAL(eve::nextint(a0), tts::map([](auto e) -> v_t { return eve::ceil(eve::next(e)); }, a0));
  }
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::nextint",
             eve::test::simd::all_types_wf16)
<typename T>(tts::type<T> tgt)
{
  using eve::nextint;

  auto cases = tts::limits(tgt);

  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(nextint(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(nextint(cases.minf), cases.valmin);
    TTS_IEEE_EQUAL(nextint(cases.inf), cases.nan);
    TTS_IEEE_EQUAL(nextint(cases.zero), cases.one);
    TTS_IEEE_EQUAL(nextint(cases.mzero), cases.one);
    TTS_IEEE_EQUAL(nextint(cases.valmax), cases.inf);

    TTS_EQUAL(nextint(T{-1}), T{-0});
    TTS_EQUAL(nextint(T{1}), T{2});
  }
  else
  {
    TTS_EQUAL(nextint(T{0}), T{1});
  }
};

//==================================================================================================
// Tests for masked nextint
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::nextint[cx](eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T a0, M mask)
{
  TTS_IEEE_EQUAL(eve::nextint[mask](a0), eve::if_else(mask, eve::nextint(a0), a0));
};
