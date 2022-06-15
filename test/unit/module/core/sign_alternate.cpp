//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::sign_alternate", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sign_alternate(T())                      , T );
  TTS_EXPR_IS( eve::sign_alternate(v_t())                    , v_t );
};

//==================================================================================================
// Tests for eve::sign_alternate
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::sign_alternate(eve::wide)"
        , eve::test::simd::signed_types
        , tts::generate ( tts::randoms(-100, +100)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a00, M const& mask)
{
  using eve::detail::map;
  using eve::sign_alternate;
  using eve::saturated;
  using eve::as;
  using v_t = eve::element_type_t<T>;
  auto a0 = eve::trunc(a00);
  TTS_EQUAL(sign_alternate(a0)      , map([](auto e) -> v_t { return eve::is_odd(e) ? v_t(-1) : v_t(1); }, a0) );
  TTS_EQUAL(sign_alternate[mask](a0), eve::if_else(mask,sign_alternate(a0),a0));

};
