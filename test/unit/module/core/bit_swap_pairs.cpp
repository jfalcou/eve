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
//  bit_swap_pairs simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_swap_pairs(simd) on integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_swap_pairs;

  // full scalar
  TTS_EQUAL(eve::bit_swap_pairs(0b01010101, 0, 7), 0b11010100);
  TTS_EQUAL(eve::bit_swap_pairs(0b01010101, eve::index<0>, eve::index<7>), 0b11010100);

  // scalar into wide
  using wt = eve::wide<int, eve::fixed<4>>;
  TTS_EQUAL(eve::bit_swap_pairs(0b01010101, wt{0}, wt{7}), wt{0b11010100});

  // wide
  TTS_EQUAL(bit_swap_pairs(a0, 0u, 7), tts::map([](auto e) -> v_t { return eve::bit_swap_pairs(e, 0, 7u); }, a0)) << a0 << '\n';
  TTS_EQUAL(bit_swap_pairs(a0, eve::index<0>, eve::index<7>), tts::map([](auto e) -> v_t { return eve::bit_swap_pairs(e, eve::index<0>, eve::index<7>); }, a0)) << a0 << '\n';
  
  // wide masked
  TTS_EQUAL(eve::bit_swap_pairs[t](a0, 0u, 7), eve::if_else(t, eve::bit_swap_pairs(a0, 0, 7u), a0));
  TTS_EQUAL(eve::bit_swap_pairs[t](a0, eve::index<0>, eve::index<7>), eve::if_else(t, eve::bit_swap_pairs(a0, eve::index<0>, eve::index<7>), a0));

  eve::wide<int, typename T::cardinal_type> wn{[](auto i, auto) { return -i; }};
  TTS_EQUAL(eve::bit_swap_pairs[wn > 0](a0, wn, 7), a0);
};
