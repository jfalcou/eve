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
TTS_CASE_TPL("Check return types of rayleigh_kurtosis_excess", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::rayleigh_kurtosis_excess(as<T>()), T);
  TTS_EXPR_IS(eve::rayleigh_kurtosis_excess(as<v_t>()), v_t);
};

//==================================================================================================
// rayleigh_kurtosis_excess tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of rayleigh_kurtosis_excess on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;

  // the exact value, rounded to double: 0.245089300687638062849
  TTS_EQUAL(eve::rayleigh_kurtosis_excess(as<T>()), T(0.24508930068763807));

  // lower and upper bracket the exact value, whatever the precision
  TTS_EXPECT(eve::rayleigh_kurtosis_excess[eve::lower](as<T>()) <= eve::rayleigh_kurtosis_excess(as<T>()));
  TTS_EXPECT(eve::rayleigh_kurtosis_excess(as<T>())             <= eve::rayleigh_kurtosis_excess[eve::upper](as<T>()));
  TTS_RELATIVE_EQUAL(eve::rayleigh_kurtosis_excess[eve::lower](as<T>()), eve::rayleigh_kurtosis_excess[eve::upper](as<T>()), 1e-4);
};

//==================================================================================================
// rayleigh_kurtosis_excess tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of rayleigh_kurtosis_excess on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::rayleigh_kurtosis_excess[eve::lower](as<T>()), eve::rayleigh_kurtosis_excess[eve::upper](as<T>()))));
};

//==================================================================================================
// masked rayleigh_kurtosis_excess
//==================================================================================================
TTS_CASE_WITH("Check behavior of rayleigh_kurtosis_excess[mask] on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::rayleigh_kurtosis_excess[mask](eve::as(a0)), eve::if_else(mask, eve::rayleigh_kurtosis_excess(eve::as(a0)), eve::zero));
};
