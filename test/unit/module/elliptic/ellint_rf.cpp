//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/module/math.hpp>

#include <boost/math/special_functions/ellint_rf.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_rf", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_rf(T(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rf(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_rf(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rf(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rf(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::ellint_rf(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rf(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rf(T(), v_t(), T()), T);
};

//==================================================================================================
// ellint_rf  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ellint_rf on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 100.0), tts::randoms(0, 100.0), tts::randoms(0, 100.0)))
<typename T>(T const& x, T const& y, T const& z)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::ellint_rf(x, y, z),
      map([](auto e, auto f, auto g) -> v_t { return boost::math::ellint_rf(e, f, g); }, x, y, z),
      11);
};


//==================================================================================================
// Tests for masked ellint_rf
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ellint_rf)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         T const& a2,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ellint_rf[mask](a0, a1, a2),
            eve::if_else(mask, eve::ellint_rf(a0, a1, a2), a0));
};
