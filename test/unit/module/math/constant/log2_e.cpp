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
TTS_CASE_TPL("Check return types of log2_e", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::log2_e(as<T>()), T);
  TTS_EXPR_IS(eve::log2_e(as<v_t>()), v_t);
};
//==================================================================================================
// log2_e  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of log2_e on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::log2_e[eve::downward](as<elt_t>()) < std::log2(std::exp(1.0l)));
    TTS_EXPECT(eve::log2_e[eve::upward](as<elt_t>()) > std::log2(std::exp(1.0l)));
  }
  TTS_IEEE_EQUAL(eve::log2_e(as<T>()), T(std::log2(std::exp(1.0l))));
};

//==================================================================================================
// log2_e  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of log2_e on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::log2_e[eve::downward](as<T>())), eve::log2_e[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked log2_e
//==================================================================================================
TTS_CASE_WITH("Check behavior of log2_e[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log2_e[mask](eve::as(a0)), eve::if_else(mask, eve::log2_e(eve::as(a0)), eve::zero));
};
