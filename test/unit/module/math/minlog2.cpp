//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
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
TTS_CASE_TPL( "Check return types of minlog2"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::minlog2(as<T>())  , T);
  TTS_EXPR_IS( eve::minlog2(as<v_t>()), v_t);
};

//==================================================================================================
// minlog2  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of minlog2 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp2(eve::minlog2(as<T>())), eve::zero(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp2(eve::next(eve::minlog2(as<T>()))))));
};
