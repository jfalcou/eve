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
EVE_TEST_TYPES( "Check return types of pio_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::pio_2(as<T>())  , T);
  TTS_EXPR_IS( eve::pio_2(as<v_t>()), v_t);
};

//==================================================================================================
// pio_2  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of pio_2 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  TTS_EXPECT(downward(eve::pio_2)(as<elt_t>()) < 2*std::atan(1.0l));
  TTS_EXPECT(upward(eve::pio_2)(as<elt_t>())   > 2*std::atan(1.0l));
   TTS_EQUAL(eve::pio_2(as<T>()), T(2*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::pio_2)(as<T>()) <= eve::pio_2(as<T>())));
  TTS_EXPECT(eve::all(eve::pio_2(as<T>()) <= upward(eve::pio_2)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::pio_2)(as<T>()), upward(eve::pio_2)(as<T>()), 0.5);
};
