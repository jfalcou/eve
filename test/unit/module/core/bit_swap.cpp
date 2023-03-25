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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_swap", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using N = std::integral_constant<size_t, 1>;
  TTS_EXPR_IS(eve::bit_swap(T(), N()), T);
  TTS_EXPR_IS(eve::bit_swap(v_t(), N()), v_t);
};

//==================================================================================================
//  bit_swap simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_swap(simd) on unsigned types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_swap;
  using eve::detail::map;
  {
    using N = std::integral_constant<size_t, 1>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
  {
    using N = std::integral_constant<size_t, 2>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
  {
    using N = std::integral_constant<size_t, 4>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
  if constexpr(sizeof(v_t) >= 2)
  {
    using N = std::integral_constant<size_t, 8>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
  if constexpr(sizeof(v_t) >= 4)
  {
    using N = std::integral_constant<size_t, 16>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
   if constexpr(sizeof(v_t) == 8)
  {
    using N = std::integral_constant<size_t, 32>;
    TTS_EQUAL(bit_swap(a0, N()), map([](auto e) -> v_t { return bit_swap(e, N()); }, a0)) << a0 << '\n';
    TTS_EQUAL(eve::bit_swap[t](a0, N()), eve::if_else(t, eve::bit_swap(a0, N()), a0));
  }
};
