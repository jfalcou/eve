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
EVE_TEST_TYPES( "Check return types of eve::sign", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sign(T())                      , T );
  TTS_EXPR_IS( eve::sign[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( eve::sign[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( eve::sign[bool()](T())              , T );

  TTS_EXPR_IS( eve::sign(v_t())                      , v_t );
  TTS_EXPR_IS( eve::sign[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( eve::sign[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( eve::sign[bool()](v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::sign)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::sign)(v_t()) , v_t );
  }
};

//==================================================================================================
// Tests for eve::sign
//==================================================================================================
EVE_TEST( "Check behavior of eve::sign(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::sign(a0)      , map([](auto e) -> v_t { return e > 0 ? 1 :(e ? -1 : 0); }, a0) );
  TTS_EQUAL(eve::sign[mask](a0), eve::if_else(mask,eve::sign(a0),a0)                    );
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL(eve::diff(eve::sign)(a0)      , T(0) );
};
