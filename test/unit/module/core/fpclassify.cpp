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
TTS_CASE_TPL("Check return types of eve::fpclassify(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  using enum eve::fpclass_enum;
  using eve::fpcl;
  TTS_EXPR_IS(eve::fpclassify(fpcl<none>(), T()), logical<T>);
  TTS_EXPR_IS(eve::fpclassify(fpcl<none>(), v_t()), logical<v_t>);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_WITH("Check behavior of fpclassify on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax))
             )
  <typename T>(T const& a0)
{
  using eve::as;
  using eve::fpclassify;
  using enum eve::fpclass_enum;
  using eve::fpcl;

  TTS_EQUAL(fpclassify(fpcl<none>()   , a0), eve::false_(as(a0)));
  TTS_EQUAL(fpclassify(fpcl<qnan>()   , a0), eve::is_nan(a0));
  TTS_EQUAL(fpclassify(fpcl<poszero>(), a0), eve::is_eqpz(a0));
  TTS_EQUAL(fpclassify(fpcl<negzero>(), a0), eve::is_eqmz(a0));
  TTS_EQUAL(fpclassify(fpcl<posinf>() , a0), eve::is_pinf(a0));
  TTS_EQUAL(fpclassify(fpcl<neginf>() , a0), eve::is_minf(a0));
  TTS_EQUAL(fpclassify(fpcl<denorm>() , a0), eve::is_denormal(a0));
  TTS_EQUAL(fpclassify(fpcl<neg>()    , a0), eve::is_finite(a0) && eve::is_ltz(a0));
  TTS_EQUAL(fpclassify(fpcl<snan>()   , a0), eve::is_nan(a0));
  TTS_EQUAL(fpclassify(fpcl<poszero|negzero>(), a0), eve::is_eqz(a0));
  TTS_EQUAL(fpclassify(fpcl<posinf|neginf>(), a0), eve::is_infinite(a0));
};
