/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of byte_swap_adjacent", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::byte_swap_adjacent(T(), int()), T);
  TTS_EXPR_IS(eve::byte_swap_adjacent(v_t(), int()), v_t);
  TTS_EXPR_IS(eve::byte_swap_adjacent(T(), char()), T);
  TTS_EXPR_IS(eve::byte_swap_adjacent(v_t(), char()), v_t);
};

//==================================================================================================
//  byte_swap_adjacent simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of byte_swap_adjacent(simd) on unsigned types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::byte_swap_adjacent;
  using eve::bit_swap_adjacent;
  using eve::detail::map;
 if constexpr(sizeof(v_t) >= 2)
 {
    int n= 1;
    TTS_EQUAL(byte_swap_adjacent(a0, n), map([n](auto e) -> v_t { return byte_swap_adjacent(e, n); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::byte_swap_adjacent[t](a0, n), eve::if_else(t, eve::byte_swap_adjacent(a0, n), a0));
  }
  if constexpr(sizeof(v_t) >= 4)
  {
    int n= 2;
    TTS_EQUAL(byte_swap_adjacent(a0, n), map([n](auto e) -> v_t { return byte_swap_adjacent(e, n); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::byte_swap_adjacent[t](a0, n), eve::if_else(t, eve::byte_swap_adjacent(a0, n), a0));
  }
  if constexpr(sizeof(v_t) >= 8)
  {
    int n= 4;
    TTS_EQUAL(byte_swap_adjacent(a0, n), map([n](auto e) -> v_t { return byte_swap_adjacent(e, n); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::byte_swap_adjacent[t](a0, n), eve::if_else(t, eve::byte_swap_adjacent(a0, n), a0));
  }
};
