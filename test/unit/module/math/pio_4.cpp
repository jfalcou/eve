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
EVE_TEST_TYPES( "Check return types of pio_4"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::pio_4(as<T>())  , T);
  TTS_EXPR_IS( eve::pio_4(as<v_t>()), v_t);
};

//==================================================================================================
// pio_4  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of pio_4 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    using elt_t = eve::element_type_t<T>;
    TTS_EXPECT(downward(eve::pio_4)(as<elt_t>()) < std::atan(1.0l));
    TTS_EXPECT(upward(eve::pio_4)(as<elt_t>())   > std::atan(1.0l));
  }
  TTS_EQUAL(eve::pio_4(as<T>()), T(std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::pio_4)(as<T>()) <= eve::pio_4(as<T>())));
  TTS_EXPECT(eve::all(eve::pio_4(as<T>()) <= upward(eve::pio_4)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::pio_4)(as<T>()), upward(eve::pio_4)(as<T>()), 0.5);
};
