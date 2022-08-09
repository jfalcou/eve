//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/module/math.hpp>

#include <boost/math/special_functions/ellint_d.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_d", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_d(T()), T);
  TTS_EXPR_IS(eve::ellint_d(v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_d(T(), T()), T);
  TTS_EXPR_IS(eve::ellint_d(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_d(T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_d(v_t(), T()), T);
};

//==================================================================================================
// ellint_d  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ellint_d on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 1.0), tts::randoms(0, eve::pio_2)))
<typename T>(T const& k, T const& phi)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::ellint_d(k), map([](auto e) -> v_t { return boost::math::ellint_d(e); }, k), 24);
  TTS_ULP_EQUAL(eve::ellint_d(phi, k),
                map([](auto e, auto f) -> v_t { return boost::math::ellint_d(e, f); }, k, phi),
                24);
};
