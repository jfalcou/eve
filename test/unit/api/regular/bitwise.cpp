//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// type tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of bitwise operators on wide", eve::test::simd::all_types)
<typename T>(tts::type<T>)
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

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of bitwise operators on eve::wide"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(0, 100)
                        , tts::randoms(0, 100)
                        )
        )
<typename T>(T a0, T a1)
{
  TTS_IEEE_EQUAL( (a0 & a1), T([&](auto i, auto) { return eve::bit_and(a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( (a0 | a1), T([&](auto i, auto) { return eve::bit_or (a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( (a0 ^ a1), T([&](auto i, auto) { return eve::bit_xor(a0.get(i), a1.get(i)); }));
  TTS_IEEE_EQUAL( ~a0      , T([&](auto i, auto) { return eve::bit_not(a0.get(i)); }));
};

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of bitwise operators on wide and scalar"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(0, 100) )
        )
<typename T>(T a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_IEEE_EQUAL( (a0 & v_t(1)), T([&](auto i, auto) { return eve::bit_and(a0.get(i), v_t(1)); }));
  TTS_IEEE_EQUAL( (a0 | v_t(1)), T([&](auto i, auto) { return eve::bit_or (a0.get(i), v_t(1)); }));
  TTS_IEEE_EQUAL( (a0 ^ v_t(1)), T([&](auto i, auto) { return eve::bit_xor(a0.get(i), v_t(1)); }));

  TTS_IEEE_EQUAL( (v_t(1) & a0), T([&](auto i, auto) { return eve::bit_and(v_t(1), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(1) | a0), T([&](auto i, auto) { return eve::bit_or (v_t(1), a0.get(i)); }));
  TTS_IEEE_EQUAL( (v_t(1) ^ a0), T([&](auto i, auto) { return eve::bit_xor(v_t(1), a0.get(i)); }));
};
