//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of euler"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::euler(as<T>())  , T);
  TTS_EXPR_IS( eve::euler(as<v_t>()), v_t);
};

//==================================================================================================
// e  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of e on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  TTS_EXPECT(downward(eve::euler)(as<elt_t>()) < std::exp(1.0l));
  TTS_EXPECT(upward(eve::euler)(as<elt_t>()) > std::exp(1.0l));
  TTS_EQUAL(eve::euler(as<T>()), T(std::exp(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::euler)(as<T>()) <= eve::euler(as<T>())));
  TTS_EXPECT(eve::all(eve::euler(as<T>()) <= upward(eve::euler)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::euler)(as<T>()), upward(eve::euler)(as<T>()), 0.5);
};
