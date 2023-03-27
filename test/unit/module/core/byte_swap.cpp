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
TTS_CASE_TPL("Check return types of byte_swap", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using N = std::integral_constant<size_t, 1>;
  TTS_EXPR_IS(eve::byte_swap(T(), N()), T);
  TTS_EXPR_IS(eve::byte_swap(v_t(), N()), v_t);
};

//==================================================================================================
//  byte_swap simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of byte_swap(simd) on unsigned types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::byte_swap;
  using eve::bit_swap;
  using eve::detail::map;
 if constexpr(sizeof(v_t) >= 2)
 {
    using N = std::integral_constant<size_t, 1>;
    using N8= std::integral_constant<size_t, 8>;
    TTS_EQUAL(byte_swap(a0, N()), bit_swap(a0, N8()));
    TTS_EQUAL(eve::byte_swap[t](a0, N()), eve::if_else(t, eve::byte_swap(a0, N()), a0));
  }
  if constexpr(sizeof(v_t) >= 4)
  {
    using N = std::integral_constant<size_t, 2>;
    using N8= std::integral_constant<size_t, 16>;
    TTS_EQUAL(byte_swap(a0, N()), bit_swap(a0, N8()));
    TTS_EQUAL(eve::byte_swap[t](a0, N()), eve::if_else(t, eve::byte_swap(a0, N()), a0));
  }
  if constexpr(sizeof(v_t) >= 8)
  {
    using N = std::integral_constant<size_t, 4>;
    using N8= std::integral_constant<size_t, 32>;
    TTS_EQUAL(byte_swap(a0, N()), bit_swap(a0, N8()));
    TTS_EQUAL(eve::byte_swap[t](a0, N()), eve::if_else(t, eve::byte_swap(a0, N()), a0));
  }
};
