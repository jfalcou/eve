//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
TTS_CASE_TPL( "Check return types of atanh"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atanh(T())  , T);
  TTS_EXPR_IS( eve::atanh(v_t()), v_t);
};

//==================================================================================================
// atanh  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of atanh on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1.0, 1.0)
                             )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atanh(a0)      , map([](auto e) -> v_t { return std::atanh(e); }, a0), 2);
  
};
