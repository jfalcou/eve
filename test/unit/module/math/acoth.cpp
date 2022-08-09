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
TTS_CASE_TPL( "Check return types of acoth"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acoth(T())  , T);
  TTS_EXPR_IS( eve::acoth(v_t()), v_t);
};

//==================================================================================================
// acoth  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of acoth on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1.0, 1e20))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acoth(a0)      , map([](auto e) -> v_t { return std::atanh(1/e); }, a0), 2);

};
