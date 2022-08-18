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

#include <boost/math/special_functions/ellint_rg.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_rg", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_rg(T(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rg(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_rg(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rg(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rg(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::ellint_rg(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rg(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rg(T(), v_t(), T()), T);
};

//==================================================================================================
// ellint_rg  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ellint_rg on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 100.0), tts::randoms(0, 100.0), tts::randoms(0, 100.0)))
<typename T>(T const& x, T const& y, T const& z)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::ellint_rg(x, y, z),
      map([](auto e, auto f, auto g) -> v_t { return boost::math::ellint_rg(e, f, g); }, x, y, z),
      11);
};


//==================================================================================================
// Tests for masked ellint_rg
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ellint_rg)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0),
                            tts::randoms(0.0, 100.0),
                            tts::randoms(0.0, 100.0),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         T const& a2,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ellint_rg[mask](a0, a1, a2),
            eve::if_else(mask, eve::ellint_rg(a0, a1, a2), a0));
};
