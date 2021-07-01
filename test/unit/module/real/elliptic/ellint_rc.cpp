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
#include <eve/function/ellint_rc.hpp>
#include <boost/math/special_functions/ellint_rc.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_rc"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_rc(T(), T())  , T);
  TTS_EXPR_IS( eve::ellint_rc(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_rc(T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rc(v_t(), T()), T);
};

//==================================================================================================
// ellint_rc  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_rc on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 100.0)
                             , eve::test::randoms(0, 100.0))
        )
<typename T>(T const& x, T const& y)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_rc(x, y) , map([](auto e, auto f) -> v_t { return boost::math::ellint_rc(e, f); }, x, y), 11);
};
