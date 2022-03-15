//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/elliptic.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_rd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_rd(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::ellint_rd(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_rd(T(), v_t(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rd(v_t(), T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rd(v_t(), v_t(), T()), T);
  TTS_EXPR_IS( eve::ellint_rd(T(), T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_rd(v_t(), T(), T()), T);
  TTS_EXPR_IS( eve::ellint_rd(T(), v_t(), T()), T);
};

//==================================================================================================
// ellint_rd  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_rd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 100.0)
                             , eve::test::randoms(0, 100.0)
                             , eve::test::randoms(0, 100.0))
        )
<typename T>(T const& x, T const& y, T const& z)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_rd(x, y, z) , map([](auto e, auto f, auto g) -> v_t { return boost::math::ellint_rd(e, f, g); }, x, y, z), 11);
};
