//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/ellint_3.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_3"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_3(T(), T()), T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), v_t()), v_t);
//   TTS_EXPR_IS( eve::ellint_3(T(), v_t()), T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), T()), T);
//   TTS_EXPR_IS( eve::ellint_3(T(), T(), T())  , T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), v_t(), v_t()), v_t);
//   TTS_EXPR_IS( eve::ellint_3(T(), v_t(), v_t()), T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), v_t(), T()), T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), T(), v_t()), T);
//   TTS_EXPR_IS( eve::ellint_3(T(), T(), v_t()), T);
//   TTS_EXPR_IS( eve::ellint_3(v_t(), T(), T()), T);
};

//==================================================================================================
// ellint_3  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_3 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 1.0)
                             , eve::test::randoms(0, 1.0)
                             , eve::test::randoms(0, eve::pio_2))
        )
<typename T>(T const& n, T const& k, T const& phi)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_3(n, k)      , map([](auto e, auto f) -> v_t { return boost::math::ellint_3(e, f); }, n, k), 10);
  TTS_ULP_EQUAL(eve::ellint_3(n, phi, k) , map([](auto e, auto f, auto g) -> v_t { return boost::math::ellint_3(e, f, g); }, k, n, phi), 10);
};
