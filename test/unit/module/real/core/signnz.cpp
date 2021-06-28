//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/diff/signnz.hpp>
#include <eve/function/pedantic/signnz.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::signnz", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::signnz(T())                      , T );
  TTS_EXPR_IS( eve::signnz[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( eve::signnz[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( eve::signnz[bool()](T())              , T );

  TTS_EXPR_IS( eve::signnz(v_t())                      , v_t );
  TTS_EXPR_IS( eve::signnz[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( eve::signnz[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( eve::signnz[bool()](v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::signnz)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::signnz)(v_t()) , v_t );
  }
};

//==================================================================================================
// Tests for eve::signnz
//==================================================================================================
EVE_TEST( "Check behavior of eve::signnz(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::signnz(a0)      , map([](auto e) -> v_t { return e >= 0 ? 1 : -1; }, a0) );
  TTS_EQUAL(eve::signnz[mask](a0), eve::if_else(mask,eve::signnz(a0),a0)                    );
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL(eve::diff(eve::signnz)(a0)      , T(0) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::signnz)(eve::nan(eve::as<T>())),  eve::nan(eve::as<T>()));
  }
};
