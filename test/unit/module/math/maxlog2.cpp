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
TTS_CASE_TPL( "Check return types of maxlog2"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::maxlog2(as<T>())  , T);
  TTS_EXPR_IS( eve::maxlog2(as<v_t>()), v_t);
};

//==================================================================================================
// maxlog2  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of maxlog2 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp2(eve::maxlog2(as<T>())), eve::inf(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp2(eve::prev(eve::maxlog2(as<T>()))))));
};
