//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_normal(simd)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_normal(T()), logical<T>);
  TTS_EXPR_IS(eve::is_normal(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_normal
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return 2 * eve::smallestposval(tgt); });

TTS_CASE_WITH("Check behavior of eve::is_normal(simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::smallestposval, mini),
                            tts::randoms(eve::zero, eve::mindenormal),
                            tts::randoms(eve::zero, mini),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using v_t = eve::element_type_t<T>;

  auto std_is_normal = [](v_t e) -> eve::logical<v_t> {
    if constexpr (std::same_as<v_t, eve::float16_t>)
      return eve::is_finite(e) && (eve::abs(e) >= eve::smallestposval(eve::as(e)));
    else
      return std::fpclassify(e) == FP_NORMAL;
  };

  TTS_EQUAL(eve::is_normal(a0), tts::map(std_is_normal, a0));
  TTS_EQUAL(eve::is_normal(a1), tts::map(std_is_normal, a1));
  TTS_EQUAL(eve::is_normal(a2), tts::map(std_is_normal, a2));

  TTS_EQUAL(eve::is_normal[t](a0), eve::if_else(t, eve::is_normal(a0), eve::false_(eve::as(a0))));
  TTS_EQUAL(eve::is_normal[t](a1), eve::if_else(t, eve::is_normal(a1), eve::false_(eve::as(a1))));
  TTS_EQUAL(eve::is_normal[t](a2), eve::if_else(t, eve::is_normal(a2), eve::false_(eve::as(a2))));
};
