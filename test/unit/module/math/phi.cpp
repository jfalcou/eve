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
EVE_TEST_TYPES( "Check return types of phi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::phi(as<T>())  , T);
  TTS_EXPR_IS( eve::phi(as<v_t>()), v_t);
};

//==================================================================================================
// phi  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of phi on wide"
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
    TTS_EXPECT(downward(eve::phi)(as<elt_t>()) < 1.61803398874989484820458683436563811772030917980575l);
    TTS_EXPECT(upward(eve::phi)(as<elt_t>())   > 1.61803398874989484820458683436563811772030917980575l);
  }
  TTS_ULP_EQUAL(eve::phi(as<T>()), T(1.61803398874989484820458683436563811772030917980575l), 0.0);
  TTS_EXPECT(eve::all(downward(eve::phi)(as<T>()) <= eve::phi(as<T>())));
  TTS_EXPECT(eve::all(eve::phi(as<T>()) <= upward(eve::phi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::phi)(as<T>()), upward(eve::phi)(as<T>()), 0.5);
};
