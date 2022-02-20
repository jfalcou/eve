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
EVE_TEST_TYPES( "Check return types of eve::m1to", eve::test::simd::signed_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::m1to(T())                      , T );
  TTS_EXPR_IS( eve::m1to(v_t())                    , v_t );
};

//==================================================================================================
// Tests for eve::m1to
//==================================================================================================
EVE_TEST( "Check behavior of eve::m1to(eve::wide)"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using eve::m1to;
  using eve::saturated;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(m1to(a0)      , map([](auto e) -> v_t { return eve::is_odd(e) ? v_t(-1) : v_t(1); }, a0) );
  TTS_EQUAL(m1to[mask](a0), eve::if_else(mask,m1to(a0),a0)    );
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL ( eve::diff(eve::m1to)(a0), eve::mone(eve::as(a0)));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::m1to variants on wide"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::saturated(eve::m1to)(T(1)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::m1to)(T(2)               ) , T(-1)           );
    TTS_EQUAL(eve::saturated(eve::m1to)(static_cast<T>(-2) ) , T(3)            );
    TTS_EQUAL(eve::saturated(eve::m1to)(eve::valmin(eve::as<T>())   ) , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::m1to)(eve::inc(eve::valmin(eve::as<T>())))          , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::m1to)(eve::inc(eve::inc(eve::valmin(eve::as<T>())))), eve::valmax(eve::as<T>()));
  }

  if constexpr(eve::unsigned_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::m1to)(T(2)), T(0));
    TTS_EQUAL(eve::saturated(eve::m1to)(T(1)), T(0));
    TTS_EQUAL(eve::saturated(eve::m1to)(T(0)), T(1));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::m1to)(T(-0.)), T(1));
    TTS_EQUAL(eve::saturated(eve::m1to)(T( 0 )), T(1));
  }
};
