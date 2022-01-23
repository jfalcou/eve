//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/elliptic.hpp>
#include <boost/math/special_functions/ellint_d.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_d"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_d(T())  , T);
  TTS_EXPR_IS( eve::ellint_d(v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_d(T(), T())  , T);
  TTS_EXPR_IS( eve::ellint_d(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_d(T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_d(v_t(), T()), T);
};

//==================================================================================================
// ellint_d  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_d on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 1.0)
                             , eve::test::randoms(0, eve::pio_2))
        )
<typename T>(T const& k, T const& phi)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_d(k)      , map([](auto e) -> v_t { return boost::math::ellint_d(e); }, k), 24);
  TTS_ULP_EQUAL(eve::ellint_d(phi, k) , map([](auto e, auto f) -> v_t { return boost::math::ellint_d(e, f); }, k, phi), 24);
};
