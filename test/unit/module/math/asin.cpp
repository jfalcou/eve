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
TTS_CASE_TPL( "Check return types of asin"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asin(T())  , T);
  TTS_EXPR_IS( eve::asin(v_t()), v_t);
};

//==================================================================================================
// asin  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of asin on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1, 1))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asin(a0)      , map([](auto e) -> v_t { return std::asin(e); }, a0), 2);
  
};
