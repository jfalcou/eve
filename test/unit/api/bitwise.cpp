//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_xor.hpp>

//==================================================================================================
// type tests
//==================================================================================================
auto type_tests  = []<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( T()    & T()   , T);
  TTS_EXPR_IS( T()    & v_t() , T);
  TTS_EXPR_IS( v_t()  & T()   , T);
  TTS_EXPR_IS( T()    | T()   , T);
  TTS_EXPR_IS( T()    | v_t() , T);
  TTS_EXPR_IS( v_t()  | T()   , T);
  TTS_EXPR_IS( T()    ^ T()   , T);
  TTS_EXPR_IS( T()    ^ v_t() , T);
  TTS_EXPR_IS( v_t()  ^ T()   , T);
  TTS_EXPR_IS( ~T()           , T);
};

EVE_TEST_BED( "Check return types of bitwise operators on eve::wide"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , type_tests
            );

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
auto simd_tests  = []<typename T>(T a0, T a1)
{
  TTS_IEEE_EQUAL( (a0 & a1), T([&](auto i, auto) { return eve::bit_and(a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( (a0 | a1), T([&](auto i, auto) { return eve::bit_or (a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( (a0 ^ a1), T([&](auto i, auto) { return eve::bit_xor(a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( ~a0      , T([&](auto i, auto) { return eve::bit_not(a0.get(i)); }));
};

EVE_TEST_BED( "Check behavior of bitwise operators on eve::wide"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::randoms(-50, 50)
                                  )
            , simd_tests
            );

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
auto mixed_tests  = []<typename T>(T a0, T)
{
  using v_t = eve::element_type_t<T>;

  TTS_IEEE_EQUAL( (a0 & v_t(1)), T([&](auto i, auto) { return eve::bit_and(a0.get(i), v_t(1)); }));
  TTS_IEEE_EQUAL( (a0 | v_t(1)), T([&](auto i, auto) { return eve::bit_or (a0.get(i), v_t(1)); }));
  TTS_IEEE_EQUAL( (a0 ^ v_t(1)), T([&](auto i, auto) { return eve::bit_xor(a0.get(i), v_t(1)); }));

  TTS_IEEE_EQUAL( (v_t(1) & a0), T([&](auto i, auto) { return eve::bit_and(v_t(1), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(1) | a0), T([&](auto i, auto) { return eve::bit_or (v_t(1), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(1) ^ a0), T([&](auto i, auto) { return eve::bit_xor(v_t(1), a0.get(i)); }));
};

EVE_TEST_BED( "Check behavior of bitwise operators on wide and scalar"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::randoms(-50, 50)
                                  )
            , mixed_tests
            );
