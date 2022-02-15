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
EVE_TEST_TYPES( "Check return types of invsqrtpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invsqrtpi(as<T>())  , T);
  TTS_EXPR_IS( eve::invsqrtpi(as<v_t>()), v_t);
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
  TTS_EXPECT(eve::invsqrtpi(as<float>()) > 0.564189583547756286948079451560772585844050629329l);
  TTS_EXPECT(downward(eve::invsqrtpi)(as<float>()) < 0.564189583547756286948079451560772585844050629329l);
  TTS_EXPECT(upward(eve::invsqrtpi)(as<float>())   >  0.564189583547756286948079451560772585844050629329l);
  TTS_EQUAL(eve::invsqrtpi(as<T>()), T(0.564189583547756286948079451560772585844050629329l));
  TTS_EXPECT(eve::all(downward(eve::invsqrtpi)(as<T>()) <= eve::invsqrtpi(as<T>())));
  TTS_EXPECT(eve::all(eve::invsqrtpi(as<T>()) <= upward(eve::invsqrtpi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invsqrtpi)(as<T>()), upward(eve::invsqrtpi)(as<T>()), 0.5);
};
