//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "std_proxy.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::argpi(simd)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::argpi(T()), T);
  TTS_EXPR_IS(eve::argpi[eve::pedantic](T()), T);

  TTS_EXPR_IS(eve::argpi(v_t()), v_t);
  TTS_EXPR_IS(eve::argpi[eve::pedantic](v_t()), v_t);
};

//==================================================================================================
// Tests for eve::argpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::argpi(simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::argpi(a0),
            tts::map([](auto e) -> v_t { return e >= 0 ? 0 : eve::one(eve::as(v_t())); }, a0));
};

//==================================================================================================
// Tests for eve::argpi[eve::pedantic]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::argpi[eve::pedantic](simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T a0)
{
  using v_t = eve::element_type_t<T>;

  auto cases = tts::limits(tts::type<T> {});

  TTS_EQUAL(eve::argpi[eve::pedantic](a0),
            tts::map([](auto e) -> v_t { return e >= 0 ? 0 : eve::one(eve::as(v_t())); }, a0));
  TTS_IEEE_EQUAL(eve::argpi[eve::pedantic](cases.nan), cases.nan);
};


//==================================================================================================
// Tests for masked argpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::argpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::argpi[mask](a0),
            eve::if_else(mask, eve::argpi(a0), a0));
};
