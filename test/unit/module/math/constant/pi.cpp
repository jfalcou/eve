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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pi(as<T>()), T);
  TTS_EXPR_IS(eve::pi(as<v_t>()), v_t);
};
//==================================================================================================
// pi  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::pi[eve::lower](as<elt_t>()) < 4 * std::atan(1.0l));
    TTS_EXPECT(eve::pi[eve::upper](as<elt_t>()) > 4 * std::atan(1.0l));
  }
  TTS_EQUAL(eve::pi(as<T>()), T(4 * std::atan(1.0l)));
};

//==================================================================================================
// pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::pi[eve::lower](as<T>())), eve::pi[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of pi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::pi[mask](eve::as(a0)), eve::if_else(mask, eve::pi(eve::as(a0)), eve::zero));
};
