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
EVE_TEST_TYPES( "Check return types of invlog10_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invlog10_2(as<T>())  , T);
  TTS_EXPR_IS( eve::invlog10_2(as<v_t>()), v_t);
};

//==================================================================================================
// invlog10_2  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invlog10_2 on wide"
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
    TTS_EXPECT(downward(eve::invlog10_2)(as<elt_t>()) < 3.3219280948873623478703194294893901758648313930246l);
    TTS_EXPECT(upward(eve::invlog10_2)(as<elt_t>())   > 3.3219280948873623478703194294893901758648313930246l);
  }
  TTS_EQUAL(eve::invlog10_2(as<T>()), T(3.3219280948873623478703194294893901758648313930246l));
  TTS_EXPECT(eve::all(downward(eve::invlog10_2)(as<T>()) <= eve::invlog10_2(as<T>())));
  TTS_EXPECT(eve::all(eve::invlog10_2(as<T>()) <= upward(eve::invlog10_2)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invlog10_2)(as<T>()), upward(eve::invlog10_2)(as<T>()), 0.5);
};
