/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_select", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::bit_select(T(), T(), T()), T);
  TTS_EXPR_IS(eve::bit_select(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::bit_select(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::bit_select(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_select(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::bit_select(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_select(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// bit_select tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_select(simd) on integers",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_select;
  using eve::detail::map;
  TTS_EQUAL(bit_select(a0, a1, a2),
            map([](auto x, auto y, auto z) -> v_t { return (y & x) | (z & ~x); }, a0, a1, a2));
};
