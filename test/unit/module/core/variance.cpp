//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of variance", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::variance(T(), T()), T);
  TTS_EXPR_IS(eve::variance(T(), v_t()), T);
  TTS_EXPR_IS(eve::variance(v_t(), T()), T);
  TTS_EXPR_IS(eve::variance(v_t(), v_t()), v_t);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::variance(T(), T(), T()), T);
    TTS_EXPR_IS(eve::variance(T(), v_t(), T()), T);
    TTS_EXPR_IS(eve::variance(v_t(), T(), T()), T);
    TTS_EXPR_IS(eve::variance(T(), T(), v_t()), T);
    TTS_EXPR_IS(eve::variance(v_t(), v_t(), T()), T);
    TTS_EXPR_IS(eve::variance(v_t(), T(), v_t()), T);

    TTS_EXPR_IS(eve::variance(v_t(), v_t(), v_t()), v_t);
  }
};

//==================================================================================================
//== variance tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of variance(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::variance;
    TTS_ULP_EQUAL(variance(a0, a1, a2),
                  eve::welford_variance(a0, a1, a2), 1.5);
};


//==================================================================================================
//=== Tests for masked variance
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::variance)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::variance[mask](a0, a1),
            eve::if_else(mask, eve::variance(a0, a1), a0));
};


TTS_CASE_WITH("Check behavior of variance kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::variance;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(variance[kahan](a0, a1, a2), eve::downgrade(variance[widen](a0, a1, a2)), 0.5);

};
