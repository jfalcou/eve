//revised
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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of minlog2denormal", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::minlog2denormal(as<T>()), T);
  TTS_EXPR_IS(eve::minlog2denormal(as<v_t>()), v_t);
};
//==================================================================================================
// minlog2denormal  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog2denormal on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp2(eve::minlog2denormal(as<T>())), eve::zero(as<T>()));
};

//==================================================================================================
// minlog2denormal  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog2denormal on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::pedantic(eve::exp2)(eve::minlog2denormal(as<T>())), eve::zero(as<T>()));
  if constexpr( eve::platform::supports_denormals )
    TTS_EXPECT(eve::all(eve::is_gtz(eve::pedantic(eve::exp2)(eve::next(eve::minlog2denormal(as<T>()))))));

  double x = eve::minlog2denormal(as<double>());
  while(eve::is_nez(eve::pedantic(eve::exp2)(x))) x = eve::prev(x);
  std::cout << std::hexfloat << eve::prev(x) << std::endl;
};


//==================================================================================================
// simd Tests for masked minlog2denormal
//==================================================================================================
TTS_CASE_WITH("Check behavior of minlog2denormal[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::minlog2denormal[mask](eve::as(a0)), eve::if_else(mask, eve::minlog2denormal(eve::as(a0)), eve::zero));
};
