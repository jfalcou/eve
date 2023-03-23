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
// TTS_CASE_TPL("Check return types of bit_reverse", eve::test::simd::integers)
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   TTS_EXPR_IS(eve::bit_reverse(T()), T);
//   TTS_EXPR_IS(eve::bit_reverse(v_t()), v_t);
// };

//==================================================================================================
//  bit_reverse simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_reverse(simd) on integral types",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_reverse;
  using eve::detail::map;
  TTS_EQUAL(bit_reverse(a0), map([](auto e) -> v_t { return bit_reverse(e); }, a0));
  TTS_EQUAL(eve::bit_reverse[t](a0), eve::if_else(t, eve::bit_reverse(a0), a0));
};


//==================================================================================================
// Tests for masked bit_reverse
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::bit_reverse)(eve::wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::bit_reverse[mask](a0),
            eve::if_else(mask, eve::bit_reverse(a0), a0));
};
