//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
TTS_CASE_TPL( "Check return types of asinpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asinpi(T())  , T);
  TTS_EXPR_IS( eve::asinpi(v_t()), v_t);
};

//==================================================================================================
// asinpi  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of asinpi on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1, 1))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asinpi(a0)      , map([](auto e) -> v_t { return eve::radinpi(std::asin(e)); }, a0), 2);

};
