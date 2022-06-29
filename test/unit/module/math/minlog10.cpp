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
TTS_CASE_TPL( "Check return types of minlog10"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::minlog10(as<T>())  , T);
  TTS_EXPR_IS( eve::minlog10(as<v_t>()), v_t);
};

//==================================================================================================
// minlog10  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of minlog10 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp10(eve::minlog10(as<T>())), eve::zero(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_gtz(eve::exp10(eve::next(eve::minlog10(as<T>()))))));
};
