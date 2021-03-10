//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// Generate two subset of data, one with no 0 for / and % on integers
//==================================================================================================
auto data = []<typename T>(eve::as_<T>, auto seed)
{
  using d_t = std::array<eve::element_type_t<T>,eve::cardinal_v<T>>;

  std::mt19937 gen;
  gen.seed(seed);
  eve::prng<eve::element_type_t<T>> distr(-50,50), dist(1,100);

  d_t d0, d1, d2;
  std::for_each(d0.begin(),d0.end(), [&](auto& e) { e = distr(gen); });
  std::for_each(d1.begin(),d1.end(), [&](auto& e) { e = dist (gen); });
  std::for_each(d2.begin(),d2.end(), [&](auto& e) { e = distr(gen); });

  return std::make_tuple(d0, d1, d2);
};

//==================================================================================================
// Types tests
//==================================================================================================
auto types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( T()    + T()   , T);
  TTS_EXPR_IS( T()    - T()   , T);
  TTS_EXPR_IS( T()    * T()   , T);
  TTS_EXPR_IS( T()    / T()   , T);
  TTS_EXPR_IS( T()    + v_t() , T);
  TTS_EXPR_IS( v_t()  + T()   , T);
  TTS_EXPR_IS( T()    - v_t() , T);
  TTS_EXPR_IS( v_t()  - T()   , T);
  TTS_EXPR_IS( T()    * v_t() , T);
  TTS_EXPR_IS( v_t()  * T()   , T);
  TTS_EXPR_IS( T()    / v_t() , T);
  TTS_EXPR_IS( v_t()  / T()   , T);

  if constexpr( eve::integral_value<T> )
  {
    TTS_EXPR_IS( T() % T(), T);
    TTS_EXPR_IS( v_t()% T(), T);
    TTS_EXPR_IS( T() % v_t(), T);
  }
};

EVE_TEST_BED( "Check return types of arithmetic operators on wide"
            , eve::test::simd::all_types
            , eve::test::no_data, types_tests
            );

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1, T const& a2
                                )
{
  TTS_EQUAL( (a0 + a2), T([&](auto i, auto) { return a0.get(i) + a2.get(i); }));
  TTS_EQUAL( (a0 - a2), T([&](auto i, auto) { return a0.get(i) - a2.get(i); }));
  TTS_EQUAL( (a0 * a2), T([&](auto i, auto) { return a0.get(i) * a2.get(i); }));
  TTS_EQUAL( (a0 / a1), T([&](auto i, auto) { return a0.get(i) / a1.get(i); }));

  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL( (a0 % a1), T([&](auto i, auto) { return a0.get(i) % a1.get(i); }) );
  }
};

EVE_TEST_BED( "Check behavior of arithmetic operators on wide"
            , eve::test::simd::all_types
            , data, simd_tests
            );

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
auto mixed_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1, T const&
                                )
{
  TTS_EQUAL( (a0 + 3), T([&](auto i, auto) { return a0.get(i) + 3; }) );
  TTS_EQUAL( (a0 - 3), T([&](auto i, auto) { return a0.get(i) - 3; }) );
  TTS_EQUAL( (3 - a0), T([&](auto i, auto) { return 3 - a0.get(i); }) );
  TTS_EQUAL( (a0 * 3), T([&](auto i, auto) { return a0.get(i) * 3; }) );
  TTS_EQUAL( (a0 / 3), T([&](auto i, auto) { return a0.get(i) / 3; }) );
  TTS_EQUAL( (3 / a1), T([&](auto i, auto) { return 3 / a1.get(i); }) );

  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL( (a0 % 3), T([&](auto i, auto) { return a0.get(i) % 3; }));
    TTS_EQUAL( (3 % a1), T([&](auto i, auto) { return 3 % a1.get(i); }));
  }
};

EVE_TEST_BED( "Check behavior of arithmetic operators on wide and scalar"
            , eve::test::simd::all_types
            , data, mixed_tests
            );
