//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/logical_or.hpp>

//==================================================================================================
// type tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of logical operators on wide", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::logical<T>()    && eve::logical<T>()  , eve::logical<T>);
  TTS_EXPR_IS( eve::logical<T>()    && eve::logical<v_t>(), eve::logical<T>);
  TTS_EXPR_IS( eve::logical<v_t>()  && eve::logical<T>()  , eve::logical<T>);
  TTS_EXPR_IS( eve::logical<T>()    || eve::logical<T>()  , eve::logical<T>);
  TTS_EXPR_IS( eve::logical<T>()    || eve::logical<v_t>(), eve::logical<T>);
  TTS_EXPR_IS( eve::logical<v_t>()  || eve::logical<T>()  , eve::logical<T>);
  TTS_EXPR_IS( !eve::logical<T>()                         , eve::logical<T>);
};

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
EVE_TEST( "Check behavior of bitwise operators on eve::wide"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::logicals(0,2)
                              , eve::test::logicals(0,2)
                              )
        )
<typename T>(T a0, T a1)
{
  TTS_IEEE_EQUAL( (a0 && a1), T([&](auto i, auto) { return eve::logical_and(a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( (a0 || a1), T([&](auto i, auto) { return eve::logical_or (a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( !a0      , T([&](auto i, auto) { return eve::logical_not(a0.get(i)); }));
};

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
EVE_TEST( "Check behavior of bitwise operators on wide and scalar"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::logicals(0,2) )
        )
<typename T>(T a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_IEEE_EQUAL( (a0 && v_t(true)  ) , T([&](auto i, auto) { return eve::logical_and(a0.get(i), v_t(true)  ); }));
  TTS_IEEE_EQUAL( (a0 && v_t(false) ) , T([&](auto i, auto) { return eve::logical_and(a0.get(i), v_t(false) ); }));
  TTS_IEEE_EQUAL( (a0 || v_t(true)  ) , T([&](auto i, auto) { return eve::logical_or (a0.get(i), v_t(true)  ); }));
  TTS_IEEE_EQUAL( (a0 || v_t(false) ) , T([&](auto i, auto) { return eve::logical_or (a0.get(i), v_t(false) ); }));

  TTS_IEEE_EQUAL( (v_t(true ) && a0), T([&](auto i, auto) { return eve::logical_and(v_t(true ), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(false) && a0), T([&](auto i, auto) { return eve::logical_and(v_t(false), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(true ) || a0), T([&](auto i, auto) { return eve::logical_or (v_t(true ), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(false) || a0), T([&](auto i, auto) { return eve::logical_or (v_t(false), a0.get(i)); }));
};
