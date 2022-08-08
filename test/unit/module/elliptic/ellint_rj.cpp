//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/module/math.hpp>

#include <cmath>

#include <boost/math/special_functions/ellint_rj.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_rj", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_rj(T(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_rj(T(), v_t(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(T(), T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(T(), v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rj(T(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(T(), T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(v_t(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rj(T(), v_t(), T(), T()), T);
};

//==================================================================================================
// ellint_rj  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ellint_rj on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 100.0),
                            tts::randoms(0, 100.0),
                            tts::randoms(0, 100.0),
                            tts::randoms(0, 100.0)))
<typename T>(T const& x, T const& y, T const& z, T const& p)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_rj(x, y, z, p),
                map([](auto e, auto f, auto g, auto h) -> v_t
                    { return boost::math::ellint_rj(e, f, g, h); },
                    x,
                    y,
                    z,
                    p),
                11);
};
