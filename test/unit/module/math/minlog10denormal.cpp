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
TTS_CASE_TPL( "Check return types of minlog10denormal"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::minlog10denormal(as<T>())  , T);
  TTS_EXPR_IS( eve::minlog10denormal(as<v_t>()), v_t);
};

//==================================================================================================
// minlog10denormal  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of minlog10denormal on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp10(eve::minlog10denormal(as<T>())), eve::zero(as<T>()), 0.0);
  if constexpr(eve::platform::supports_denormals)
    TTS_EXPECT(eve::all(eve::is_gtz(eve::pedantic(eve::exp10)(eve::next(eve::minlog10denormal(as<T>()))))));
};
