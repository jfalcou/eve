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
#include <boost/math/special_functions/ellint_2.hpp>


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ellint_2(T())  , T);
  TTS_EXPR_IS( eve::ellint_2(v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_2(T(), T())  , T);
  TTS_EXPR_IS( eve::ellint_2(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::ellint_2(T(), v_t()), T);
  TTS_EXPR_IS( eve::ellint_2(v_t(), T()), T);
};

//==================================================================================================
// ellint_2  tests
//==================================================================================================
EVE_TEST( "Check behavior of ellint_2 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 1.0)
                             , eve::test::randoms(0, eve::pio_2))
        )
<typename T>(T const& k, T const& phi)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::ellint_2(k)      , map([](auto e) -> v_t { return boost::math::ellint_2(e); }, k), 10);
  TTS_ULP_EQUAL(eve::ellint_2(phi, k) , map([](auto e, auto f) -> v_t { return boost::math::ellint_2(e, f); }, k, phi), 10);
};
