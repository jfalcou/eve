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

#include <boost/math/special_functions/ellint_rc.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_rc", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_rc(T(), T()), T);
  TTS_EXPR_IS(eve::ellint_rc(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_rc(T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_rc(v_t(), T()), T);
};

//==================================================================================================
// ellint_rc  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ellint_rc on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 100.0), tts::randoms(0, 100.0)))
<typename T>(T const& x, T const& y)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_rc(x, y),
                map([](auto e, auto f) -> v_t { return boost::math::ellint_rc(e, f); }, x, y),
                11);
};


//==================================================================================================
// Tests for masked ellint_rc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ellint_rc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 100.0),
                            tts::randoms(0, 100.0),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ellint_rc[mask](a0, a1),
            eve::if_else(mask, eve::ellint_rc(a0, a1), a0));
};
