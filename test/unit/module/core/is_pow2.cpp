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
TTS_CASE_TPL("Check return types of is_pow2 on wide", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::is_pow2(T()), eve::logical<T>);
  TTS_EXPR_IS(eve::is_pow2(v_t()), eve::logical<v_t>);
};

//==================================================================================================
// is_pow2(simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of is_pow2(wide) on unsigned integral ",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::ramp(1)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_floating_point_t<v_t>;
  TTS_EQUAL(eve::is_pow2(a0),
            map([](auto e) -> eve::logical<v_t>
                { return std::exp2(std::trunc(std::log2(f_t(e)))) == f_t(e); },
                a0));
};
