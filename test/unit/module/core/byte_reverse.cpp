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
TTS_CASE_TPL("Check return types of byte_reverse", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::byte_reverse(T()), T);
  TTS_EXPR_IS(eve::byte_reverse(v_t()), v_t);
};

//==================================================================================================
//  byte_reverse simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of byte_reverse(simd) on integral types",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(sizeof(v_t) == 8)
  {
    using eve::byte_reverse;
    using eve::detail::map;
    TTS_EQUAL(byte_reverse(a0), map([](auto e) -> v_t { return byte_reverse(e); }, a0));
    TTS_EQUAL(eve::byte_reverse[t](a0), eve::if_else(t, eve::byte_reverse(a0), a0));
  }
};


//==================================================================================================
// Tests for masked byte_reverse
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::byte_reverse)(eve::wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::byte_reverse[mask](a0),
            eve::if_else(mask, eve::byte_reverse(a0), a0));
};
