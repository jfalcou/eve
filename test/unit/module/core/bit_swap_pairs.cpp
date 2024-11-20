/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <bit>

TTS_CASE_TPL("Check eve::bit_swap_pairs return type", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::bit_swap_pairs(T{}, T{}, T{}), T);
  TTS_EXPR_IS(eve::bit_swap_pairs(T{}, v_t{}, v_t{}), T);
  TTS_EXPR_IS(eve::bit_swap_pairs(v_t{}, v_t{}, v_t{}), v_t);
};

TTS_CASE_WITH("Check behavior of bit_swap_pairs(simd) on integral types",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::bit_swap_pairs(a0, 0u, 7u), tts::map([](auto e) -> v_t { return eve::bit_swap_pairs(e, 0u, 7u); }, a0)) << a0 << '\n';
  TTS_EQUAL(eve::bit_swap_pairs[t](a0, 0u, 7u), eve::if_else(t, eve::bit_swap_pairs(a0, 0u, 7u), a0));

  eve::wide<int, typename T::cardinal_type> wn{[](auto i, auto) { return -i; }};
  TTS_EQUAL(eve::bit_swap_pairs[wn > 0](a0, wn, 7), a0);
};
