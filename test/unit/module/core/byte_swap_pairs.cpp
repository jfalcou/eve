/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <bit>

//==================================================================================================
//  byte_swap_pairs simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of byte_swap_pairs(simd) on integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  constexpr size_t S = sizeof(v_t);
  constexpr auto _0 = std::integral_constant<size_t, 0>();
  constexpr auto _S = std::integral_constant<size_t, S-1>();
  constexpr auto _H = std::integral_constant<size_t, S/2>();
  using eve::byte_swap_pairs;
  using eve::detail::map;
  TTS_EQUAL(byte_swap_pairs(a0, _0, _S), map([_0, _S](auto e) -> v_t { return eve::byte_swap_pairs(e, _0, _S); }, a0));
  TTS_EQUAL(eve::byte_swap_pairs[t](a0, _0, _S), eve::if_else(t, eve::byte_swap_pairs(a0, _0, _S), a0));
  TTS_EQUAL(byte_swap_pairs(a0, _0, _H), map([_0, _H](auto e) -> v_t { return eve::byte_swap_pairs(e, _0, _H); }, a0));
  TTS_EQUAL(eve::byte_swap_pairs[t](a0, _0, _H), eve::if_else(t, eve::byte_swap_pairs(a0, _0, _H), a0));
};
