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
EVE_TEST_TYPES( "Check return types of invsqrt_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invsqrt_2(as<T>())  , T);
  TTS_EXPR_IS( eve::invsqrt_2(as<v_t>()), v_t);
};

//==================================================================================================
// invsqrt_2  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invsqrt_2 on wide"
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
    TTS_EXPECT(downward(eve::invsqrt_2)(as<elt_t>()) <= (1.0l/(std::sqrt(2.0l))));
    TTS_EXPECT(  upward(eve::invsqrt_2)(as<elt_t>()) >= (1.0l/(std::sqrt(2.0l))));
  }
  TTS_ULP_EQUAL(eve::invsqrt_2(as<T>()), T(1.0l/(std::sqrt(2.0l))), 0.5);
  TTS_EXPECT(eve::all(downward(eve::invsqrt_2)(as<T>()) <= eve::invsqrt_2(as<T>())));
  TTS_EXPECT(eve::all(  upward(eve::invsqrt_2)(as<T>()) >= eve::invsqrt_2(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invsqrt_2)(as<T>()), upward(eve::invsqrt_2)(as<T>()), 0.5);
};
