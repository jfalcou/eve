//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

auto data = []<typename T>(eve::as_<T>, auto seed)
{
  using d_t = std::array<eve::element_type_t<T>,eve::cardinal_v<T>>;

  std::mt19937 gen;
  gen.seed(seed);
  eve::prng<eve::element_type_t<T>> dist0(-50,50), dist1(1,100), dist2(-50,50);

  d_t d0, d1, d2;
  std::for_each(d0.begin(),d0.end(), [&](auto& e) { e = dist0(gen); });
  std::for_each(d1.begin(),d1.end(), [&](auto& e) { e = dist1(gen); });
  std::for_each(d2.begin(),d2.end(), [&](auto& e) { e = dist2(gen); });

  return std::make_tuple(d0, d1, d2);
};

auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1, T const& a2
                                )
{
  T ref_add([&](auto i, auto) { return a0.get(i) + a2.get(i); });
  T ref_sub([&](auto i, auto) { return a0.get(i) - a2.get(i); });
  T ref_mul([&](auto i, auto) { return a0.get(i) * a2.get(i); });
  T ref_div([&](auto i, auto) { return a0.get(i) / a1.get(i); });

  TTS_EXPR_IS( a0 + a2, T);
  TTS_EXPR_IS( a0 - a2, T);
  TTS_EXPR_IS( a0 * a2, T);
  TTS_EXPR_IS( a0 / a1, T);
  if constexpr( eve::integral_value<T> ) TTS_EXPR_IS( a0 % a1, T);

  TTS_EQUAL( (a0 + a2), ref_add );
  TTS_EQUAL( (a0 - a2), ref_sub );
  TTS_EQUAL( (a0 * a2), ref_mul );
  TTS_EQUAL( (a0 / a1), ref_div );

  if constexpr( eve::integral_value<T> )
  {
    T ref_mod([&](auto i, auto) { return a0.get(i) % a1.get(i); });
    TTS_EQUAL( (a0 % a1), ref_mod );
  }
};

EVE_TEST_BED( "Check behavior of arithmetic operators on eve::wide"
            , eve::test::simd::all_types
            , data, simd_tests
            );
