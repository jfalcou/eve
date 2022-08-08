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
TTS_CASE_TPL( "Check return types of atan"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atan(T())  , T);
  TTS_EXPR_IS( eve::atan(v_t()), v_t);
};

//==================================================================================================
// atan  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of atan on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atan(a0)      , map([](auto e) -> v_t { return std::atan(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::atan(a1)      , map([](auto e) -> v_t { return std::atan(e); }, a1), 2);


};
