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
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sulp(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sulp(T()), T);
  TTS_EXPR_IS(eve::sulp(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sulp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sulp(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(1)))
  <typename T>(T const& )
{
  using eve::as;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::safe_scale(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::safe_scale(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::safe_scale(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::safe_scale(eve::zero(eve::as<T>())), eve::maxflint(eve::as<T>()), 0);
  }

  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(1))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale[eve::pedantic](T(0))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(10))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(5))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(2))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(1.5))))));
  TTS_EXPECT(eve::all(eve::is_flint(eve::log2(eve::safe_scale(T(1000.6))))));

    };
