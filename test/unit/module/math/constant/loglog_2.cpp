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
// loglog_2 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of loglog_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::loglog_2(as<T>()), T);
  TTS_EXPR_IS(eve::loglog_2(as<v_t>()), v_t);
};
//==================================================================================================
// loglog_2 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of loglog_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::loglog_2[eve::downward](eve::as<T>()) <= -0.36651292058166432701243915823267l);
    TTS_EXPECT(eve::loglog_2[eve::upward](eve::as<T>()) >=   -0.36651292058166432701243915823267l);
  }
  TTS_EQUAL(eve::loglog_2(eve::as<T>()), T(std::log(std::log(2.0l))));
};

//==================================================================================================
// loglog_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of loglog_2 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::loglog_2[eve::downward](as<T>()), eve::loglog_2[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked loglog_2
//==================================================================================================
TTS_CASE_WITH("Check behavior of loglog_2[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::loglog_2[mask](eve::as(a0)), eve::if_else(mask, eve::loglog_2(eve::as(a0)), eve::zero));
};
