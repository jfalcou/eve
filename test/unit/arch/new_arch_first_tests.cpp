//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/arch/wide.hpp>

// For a new arch.
//
// After getting meta things to work, this is the first set of tests that
// need to pass.
//
// Comment out 1 by 1.

TTS_CASE("Implement basic make function for wide<int>")
{
  eve::wide<int> x {[](int i, int) { return i; }};

  (void)x;
  TTS_PASS();
};

TTS_CASE("Implement get function for wide")
{
  eve::wide<int> x {[](int i, int) { return i; }};

  for( int i = 0; i != x.size(); ++i ) { TTS_EQUAL(i, x.get(i)); }
};

TTS_CASE("Check make half wide<int>. Make sure about zeroes in the unused for less than native."
         "Note that we only guarantee zeroes in the hidden bytes for constructors")
{
  constexpr int                    size = eve::fundamental_cardinal_v<int> / 2;
  eve::wide<int, eve::fixed<size>> x {[](int i, int) { return i; }};

  for( int i = 0; i != size; ++i ) { TTS_EQUAL(i, x.get(i)); }
};

TTS_CASE_TPL("Make all wides", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t                      = eve::element_type_t<T>;
  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<e_t>;

  T x {[](int i, int) { return i; }};

  for( int i = 0; i != T::size(); ++i ) { TTS_EQUAL((e_t)i, x.get(i)); }

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && T::size() < min_n )
  {
    auto full_wide = eve::bit_cast(x, eve::as<eve::wide<e_t, eve::fixed<min_n>>> {});
    for( int i = 0; i != full_wide.size(); ++i )
    {
      e_t expected = i < T::size() ? i : 0;
      TTS_EQUAL(expected, full_wide.get(i));
    }
  }
};

TTS_CASE_TPL("All wides: set", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;

  // No splat make yet
  T x {[](int, int) { return 0; }};

  for( int i = 0; i != x.size(); ++i )
  {
    TTS_EQUAL((e_t)0, x.get(i));
    x.set(i, (e_t)(i + 1));
    TTS_EQUAL((e_t)(i + 1), x.get(i));
  }
};

TTS_CASE("make wide<int>, splat")
{
  eve::wide<int> x {3};
  for( int i = 0; i != x.size(); ++i ) { TTS_EQUAL(3, x.get(i)); }
};

TTS_CASE_TPL("Make all wides, splat", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t                      = eve::element_type_t<T>;
  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<e_t>;

  T x {(e_t)3};

  for( int i = 0; i != x.size(); ++i ) { TTS_EQUAL((e_t)3, x.get(i)); }

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && T::size() < min_n )
  {
    auto full_wide = eve::bit_cast(x, eve::as<eve::wide<e_t, eve::fixed<min_n>>> {});
    for( int i = 0; i != full_wide.size(); ++i )
    {
      e_t expected = i < T::size() ? 3 : 0;
      TTS_EQUAL(expected, full_wide.get(i));
    }
  }
};

TTS_CASE("Slice, wide<int>")
{
  eve::wide<int> x {[](int i, int) { return i + 1; }};
  auto [l, h] = x.slice();

  int i = 0;
  for( ; i != eve::wide<int>::size() / 2; ++i ) TTS_EQUAL(l.get(i), i + 1);
  for( ; i != eve::wide<int>::size(); ++i )
    TTS_EQUAL(h.get(i - (eve::wide<int>::size() / 2)), i + 1);
};

TTS_CASE_TPL("Slice all wides", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( T::size() == 1 ) { TTS_PASS(); }
  else
  {
    using e_t = eve::element_type_t<T>;

    T x {[](int i, int) { return i + 1; }};
    auto [l, h] = x.slice();

    int i = 0;
    for( ; i != T::size() / 2; ++i ) TTS_EQUAL(l.get(i), (e_t)(i + 1));
    for( ; i != T::size(); ++i ) TTS_EQUAL(h.get(i - (T::size() / 2)), (e_t)(i + 1));
  }
};

TTS_CASE("Make aggregated logical")
{
  using N = eve::fixed<eve::expected_cardinal_v<double> * 2>;
  eve::logical<eve::wide<double, N>> l {[](int i, int) { return i % 2 == 0; }};

  for( int i = 0; i != l.size(); ++i )
  {
    bool test = i % 2 == 0;
    TTS_EQUAL(test, l.get(i)) << i;
  }
};


TTS_CASE_TPL("Make all logicals", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t                      = eve::element_type_t<T>;
  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<e_t>;

  eve::logical<T> x {[](int i, int) { return i % 2 == 0; }};

  for( int i = 0; i != T::size(); ++i )
  {
    bool test = i % 2 == 0;
    TTS_EQUAL(test, x.get(i));
  }

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && T::size() < min_n )
  {
    auto full = eve::bit_cast(x, eve::as<eve::logical<eve::wide<e_t, eve::fixed<min_n>>>> {});
    for( int i = 0; i != full.size(); ++i )
    {
      bool test = (i < T::size()) ? i % 2 == 0 : false;
      TTS_EQUAL(test, full.get(i)) << i;
    }
  }
};

TTS_CASE_TPL("Make all logicals (splat)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t                      = eve::element_type_t<T>;
  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<e_t>;

  eve::logical<T> x {true}, y {false};

  for( int i = 0; i != T::size(); ++i )
  {
    TTS_EXPECT(x.get(i));
    TTS_EXPECT_NOT(y.get(i));
  }

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && T::size() < min_n )
  {
    using full_t = eve::logical<eve::wide<e_t, eve::fixed<min_n>>>;
    auto full_x = eve::bit_cast(x, eve::as<full_t>{});
    auto full_y = eve::bit_cast(y, eve::as<full_t>{});
    for( int i = 0; i != full_x.size(); ++i )
    {
      TTS_EQUAL(i < T::size(), full_x.get(i));
      TTS_EXPECT_NOT(full_y.get(i));
    }
  }
};

TTS_CASE("Wide<int> equals") {
  eve::wide<int> x{3};
  TTS_EQUAL(x, x);
};

TTS_CASE("logical<Wide<int>> equals") {
  eve::wide<int> x{3};
  TTS_EQUAL((x != 0), (x != 0));
};
