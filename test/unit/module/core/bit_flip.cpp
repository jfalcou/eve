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
//  bit_flip simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_flip(simd) on integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_flip;
  using eve::detail::map;
  TTS_EQUAL(bit_flip(a0, 0u), map([](auto e) -> v_t { return eve::bit_flip(e, 0u); }, a0));
  TTS_EQUAL(eve::bit_flip[t](a0, 0u), eve::if_else(t, eve::bit_flip(a0, 0u), a0));
};
