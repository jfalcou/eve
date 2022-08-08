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
TTS_CASE_TPL( "Check return types of asecpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asecpi(T())  , T);
  TTS_EXPR_IS( eve::asecpi(v_t()), v_t);
};

//==================================================================================================
// asecpi  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of asecpi on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1.0, 100.0)
                             , tts::randoms(1.0, eve::valmax)
                             , tts::randoms(eve::valmin, -1.0)
                             , tts::randoms(-100.0, -1.0))
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sasecpi = [](auto e) -> v_t { return eve::radinpi(std::acos(1/e)); };
  TTS_ULP_EQUAL(eve::asecpi(a0)           , map(sasecpi, a0), 2);

  TTS_ULP_EQUAL(eve::asecpi(a1)           , map(sasecpi, a1), 2);

  TTS_ULP_EQUAL(eve::asecpi(a2)           , map(sasecpi, a2), 2);

  TTS_ULP_EQUAL(eve::asecpi(a3)           , map(sasecpi, a3), 2);


};
