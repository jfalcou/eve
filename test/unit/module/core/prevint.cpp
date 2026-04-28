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
TTS_CASE_TPL("Check return types of eve::prevint", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::prevint(T{}), T);
  TTS_EXPR_IS(eve::prevint(v_t{}), v_t);
};

//==================================================================================================
//= Tests for eve::prevint
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::prevint(eve::wide)",
              eve::test::simd::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a0)
{
  if constexpr (eve::integral_value<T>)
  {
    TTS_EQUAL(eve::prevint(a0), eve::dec(a0));
  }
  else
  {
    using v_t = eve::element_type_t<T>;
    TTS_EQUAL(eve::prevint(a0), tts::map([](auto e) -> v_t { return eve::floor(eve::prev(e)); }, a0));
  }
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::prevint",
             eve::test::simd::all_types_wf16)
<typename T>(tts::type<T> tgt)
{
  using eve::prevint;

  auto cases = tts::limits(tgt);

  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(prevint(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(prevint(cases.minf), cases.nan);
    TTS_IEEE_EQUAL(prevint(cases.inf), cases.valmax);
    TTS_IEEE_EQUAL(prevint(cases.zero), cases.mone);
    TTS_IEEE_EQUAL(prevint(cases.mzero), cases.mone);
    TTS_IEEE_EQUAL(prevint(cases.valmin), cases.minf);

    TTS_EQUAL(prevint(T{-1}), T{-2});
    TTS_EQUAL(prevint(T{1}), T{0});
  }
  else
  {
    TTS_EQUAL(prevint(T{0}), T{-1});
  }
};


//==================================================================================================
// Tests for masked prevint
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::prevint[cx](eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::prevint[mask](a0), eve::if_else(mask, eve::prevint(a0), a0));
};
