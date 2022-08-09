//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of deginrad"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::deginrad(T())  , T);
  TTS_EXPR_IS( eve::deginrad(v_t()), v_t);
};

//==================================================================================================
// deginrad  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of deginrad on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_ULP_EQUAL( eve::deginrad(a0), a0*T(0.017453292519943295769236907684886), 2);
};
