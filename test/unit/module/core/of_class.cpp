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
TTS_CASE_TPL("Check return types of eve::of_class(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::of_class(T(), eve::qnan), logical<T>);
  TTS_EXPR_IS(eve::of_class(v_t(),eve::qnan), logical<v_t>);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_WITH("Check behavior of of_class on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax))
             )
  <typename T>(T const& a0)
{
  using eve::as;
  using eve::of_class;

  TTS_EQUAL(of_class(a0, eve::qnan   ), eve::is_nan(a0));
  TTS_EQUAL(of_class(a0, eve::poszero), eve::is_eqpz(a0));
  TTS_EQUAL(of_class(a0, eve::negzero), eve::is_eqmz(a0));
  TTS_EQUAL(of_class(a0, eve::posinf ), eve::is_pinf(a0));
  TTS_EQUAL(of_class(a0, eve::neginf ), eve::is_minf(a0));
  TTS_EQUAL(of_class(a0, eve::denorm ), eve::is_denormal(a0));
  TTS_EQUAL(of_class(a0, eve::neg    ), eve::is_finite(a0) && eve::is_ltz(a0));
  TTS_EQUAL(of_class(a0, eve::snan   ), eve::is_nan(a0));
  TTS_EQUAL(of_class(a0, eve::poszero|eve::negzero), eve::is_eqz(a0));
  TTS_EQUAL(of_class(a0, eve::posinf|eve::neginf), eve::is_infinite(a0));
};
