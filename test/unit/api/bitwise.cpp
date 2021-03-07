//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_xor.hpp>

auto data = []<typename T>(eve::as_<T>, auto seed)
{
  using e_t = eve::element_type_t<T>;
  using d_t = std::array<e_t,eve::cardinal_v<T>>;

  std::mt19937 gen;
  gen.seed(seed);

  eve::prng<e_t> dist(-50,50);

  d_t d0, d1;
  std::for_each(d0.begin(),d0.end(), [&](auto& e) { e = dist(gen); });
  std::for_each(d1.begin(),d1.end(), [&](auto& e) { e = dist(gen); });

  return std::make_tuple(d0, d1);
};

auto bitwise_tests  = []<typename T>(auto& runtime, bool verbose, auto const&, T a0, T a1)
{
  T ref_and([&](auto i, auto) { return eve::bit_and(a0.get(i), a1.get(i)); });
  T ref_or ([&](auto i, auto) { return eve::bit_or (a0.get(i), a1.get(i)); });
  T ref_xor([&](auto i, auto) { return eve::bit_xor(a0.get(i), a1.get(i)); });
  T ref_not([&](auto i, auto) { return eve::bit_not(a0.get(i)); });

  TTS_EXPR_IS( a0 & a1, T);
  TTS_EXPR_IS( a0 | a1, T);
  TTS_EXPR_IS( a0 ^ a1, T);
  TTS_EXPR_IS( ~a0    , T);

  TTS_IEEE_EQUAL( (a0 & a1), ref_and );
  TTS_IEEE_EQUAL( (a0 | a1), ref_or  );
  TTS_IEEE_EQUAL( (a0 ^ a1), ref_xor );
  TTS_IEEE_EQUAL( ~a0      , ref_not );
};

EVE_TEST_BED( "Check behavior of bitwise operators on eve::wide"
            , eve::test::simd::all_types
            , data, bitwise_tests
            );
