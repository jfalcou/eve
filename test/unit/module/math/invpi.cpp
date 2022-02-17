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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of invpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invpi(as<T>())  , T);
  TTS_EXPR_IS( eve::invpi(as<v_t>()), v_t);
};

//==================================================================================================
// invpi  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invpi on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    TTS_EXPECT(downward(eve::invpi)(as<elt_t>()) <= (1.0/(4*std::atan(1.0l))));
    TTS_EXPECT(  upward(eve::invpi)(as<elt_t>()) >= (1.0/(4*std::atan(1.0l))));
  }
  TTS_ULP_EQUAL(eve::invpi(as<T>()), T(1.0/(4*std::atan(1.0l))), 0.0);
  TTS_EXPECT(eve::all(downward(eve::invpi)(as<T>()) <= eve::invpi(as<T>())));
  TTS_EXPECT(eve::all(eve::invpi(as<T>()) <= upward(eve::invpi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invpi)(as<T>()), upward(eve::invpi)(as<T>()), 0.5);
};
