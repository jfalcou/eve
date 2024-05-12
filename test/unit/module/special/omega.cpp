//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of omega"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::omega(T())  ,T);
  TTS_EXPR_IS( eve::omega(v_t()), v_t);
};

//==================================================================================================
// omega  tests
//==================================================================================================
EVE_TEST( "Check behavior of omega on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(1.0, 1000)
                             , eve::test::randoms(0.0, 1.0)
                             , eve::test::randoms(-10.0, 0.0)
                             )
        )
  <typename T>(T a0, T a1, T a2)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {

    TTS_ULP_EQUAL(eve::omega(eve::nan(eve::as(a0))), eve::nan(eve::as(a0)), 0.0);
    TTS_ULP_EQUAL(eve::omega(eve::inf(eve::as(a0))), eve::inf(eve::as(a0)), 0.0);
    TTS_ULP_EQUAL(eve::omega(T(1)), T(1), 2.0);
    TTS_ULP_EQUAL(eve::omega(eve::zero(eve::as(a0))), T(0.56714329040978384011), 0.0);
    elt_t tol = 5000*eve::eps(eve::as<elt_t>());
    {
      auto z = eve::omega(eve::mone(eve::as<elt_t>()));
      auto r = eve::log(z)+z;
      TTS_RELATIVE_EQUAL(eve::mone(eve::as<elt_t>()), r, tol);
    }
    {
      auto z = eve::omega(a0);
      auto r = eve::log(z)+z;
      TTS_RELATIVE_EQUAL(a0, r, tol);
    }
    {
      auto z = eve::omega(a1);
      auto r = eve::log(z)+z;
      TTS_RELATIVE_EQUAL(a1, r, tol);
    }
   {
      auto z = eve::omega(a2);
      auto r = eve::log(z)+z;
      TTS_RELATIVE_EQUAL(a2, r, tol);
    }
  }
};
