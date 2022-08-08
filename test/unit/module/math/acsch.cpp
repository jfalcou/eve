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
TTS_CASE_TPL( "Check return types of acsch"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acsch(T())  , T);
  TTS_EXPR_IS( eve::acsch(v_t()), v_t);
};

//==================================================================================================
// acsch  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of acsch on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-1e20,1e20)
                              , tts::randoms(-100.0, 100.0)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acsch(a0)      , map([](auto e) -> v_t { return std::asinh(1/e); }, a0), 2);
  TTS_ULP_EQUAL(eve::acsch(a1)      , map([](auto e) -> v_t { return std::asinh(1/e); }, a1), 2);


};
