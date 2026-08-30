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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of extreme_value_skewness", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::extreme_value_skewness(as<T>()), T);
  TTS_EXPR_IS(eve::extreme_value_skewness(as<v_t>()), v_t);
};

//==================================================================================================
// extreme_value_skewness tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of extreme_value_skewness on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;

  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::extreme_value_skewness[eve::lower](as<elt_t>()) < 1.13954709940464865749l);
    TTS_EXPECT(eve::extreme_value_skewness[eve::upper](as<elt_t>()) > 1.13954709940464865749l);
  }
  TTS_EQUAL(eve::extreme_value_skewness(as<T>()), T(1.13954709940464865749l));
};

//==================================================================================================
// extreme_value_skewness tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of extreme_value_skewness on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::extreme_value_skewness[eve::lower](as<T>()), eve::extreme_value_skewness[eve::upper](as<T>()))));
};

//==================================================================================================
// masked extreme_value_skewness
//==================================================================================================
TTS_CASE_WITH("Check behavior of extreme_value_skewness[mask] on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::extreme_value_skewness[mask](eve::as(a0)), eve::if_else(mask, eve::extreme_value_skewness(eve::as(a0)), eve::zero));
};
