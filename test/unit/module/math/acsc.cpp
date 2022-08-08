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
TTS_CASE_TPL( "Check return types of acsc"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acsc(T())  , T);
  TTS_EXPR_IS( eve::acsc(v_t()), v_t);
};

//==================================================================================================
// acsc  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of acsc on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(1.0, 100.0)
                              , tts::randoms(1.0, 1e20)
                              , tts::randoms(-1e20, -1.0)
                              , tts::randoms(-100.0, -1.0)
                              )
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sacsc = [](auto e) -> v_t { return std::asin(1/e); };
  TTS_ULP_EQUAL(eve::acsc(a0)           , map(sacsc, a0), 2);

  TTS_ULP_EQUAL(eve::acsc(a1)           , map(sacsc, a1), 2);

  TTS_ULP_EQUAL(eve::acsc(a2)           , map(sacsc, a2), 2);

  TTS_ULP_EQUAL(eve::acsc(a3)           , map(sacsc, a3), 2);

};
