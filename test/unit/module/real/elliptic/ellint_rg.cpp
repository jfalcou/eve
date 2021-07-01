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
#include <eve/function/ellint_rg.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_rg"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_rg(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::ellint_rg(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_rg(T(), v_t(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rg(v_t(), T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rg(v_t(), v_t(), T()), T);
  TTS_EXPR_IS( eve::ellint_rg(T(), T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rg(v_t(), T(), T()), T);
  TTS_EXPR_IS( eve::ellint_rg(T(), v_t(), T()), T);
};

//==================================================================================================
// ellint_rg  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_rg on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 100.0)
                             , eve::test::randoms(0, 100.0)
                             , eve::test::randoms(0, 100.0))
        )
<typename T>(T const& x, T const& y, T const& z)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_rg(x, y, z) , map([](auto e, auto f, auto g) -> v_t { return boost::math::ellint_rg(e, f, g); }, x, y, z), 11);
};
