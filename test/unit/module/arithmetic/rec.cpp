//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/diff/rec.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::rec", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::rec(T())                      , T );
  TTS_EXPR_IS( eve::rec[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( eve::rec[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( eve::rec[bool()](T())              , T );

  TTS_EXPR_IS( eve::rec(v_t())                      , v_t );
  TTS_EXPR_IS( eve::rec[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( eve::rec[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( eve::rec[bool()](v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::rec)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::rec)(v_t()) , v_t );
  }
};

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto minimal = []<typename T>(eve::as<T> const & tgt)
{
  return -eve::smallestposval(tgt);
};

auto maximal = []<typename T>(eve::as<T> const & tgt)
{
  return eve::valmax(tgt) / 2;
};

//==================================================================================================
// Tests for eve::rec
//==================================================================================================
EVE_TEST( "Check behavior of eve::rec(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(minimal, maximal)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL ( eve::rec(a0)
                , map([](auto e) -> v_t { return e ? v_t(1/e) : eve::valmax(eve::as<v_t>()); }, a0)
                , 0.5
                );

  TTS_EQUAL(eve::rec[mask](a0), eve::if_else(mask,eve::rec(a0),a0));
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL ( eve::diff(eve::rec)(a0), -eve::rec(a0*a0));
};
