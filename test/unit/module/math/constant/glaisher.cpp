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
// glaisher Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of glaisher", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::glaisher(as<T>()), T);
  TTS_EXPR_IS(eve::glaisher(as<v_t>()), v_t);
};
//==================================================================================================
// glaisher tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of glaisher on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::glaisher[eve::lower](eve::as<T>()) <= 1.28242712910062263687l);
    TTS_EXPECT(eve::glaisher[eve::upper](eve::as<T>()) >= 1.28242712910062263687l);
  }
  TTS_EQUAL(eve::glaisher(eve::as<T>()), T(1.28242712910062263687l));
};

//==================================================================================================
// glaisher  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of glaisher on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::glaisher[eve::lower](as<T>()), eve::glaisher[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked glaisher
//==================================================================================================
TTS_CASE_WITH("Check behavior of glaisher[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::glaisher[mask](eve::as(a0)), eve::if_else(mask, eve::glaisher(eve::as(a0)), eve::zero));
};
