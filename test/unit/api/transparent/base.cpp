//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/arch/wide.hpp>

// base struct used in the test
template <typename E>
struct BS {
  eve::element_type_t<E> value;

  template <typename V>
  static BS of(V v) { return BS{ static_cast<E>(v) }; }

  bool operator==(BS const& other) const { return value == other.value; }
};

template<typename E>
struct eve::transparent_trait<BS<E>> { using type = E; };

TTS_CASE_TPL("Create & get function for wide<transparent enum>", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  W x {[](int i, int) { return static_cast<E>(i); }};

  for(int i = 0; i != x.size(); ++i ) { TTS_EQUAL(static_cast<E>(i), x.get(i)); }
};

TTS_CASE_TPL("Create & get function for wide<transparent struct>", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BS<E>;
  using W = typename Wb::template retype<S>;

  W x {[](int i, int) { return S::of(i); }};

  for(int i = 0; i != x.size(); ++i ) { TTS_EQUAL(S::of(i), x.get(i)); }
};

TTS_CASE_TPL("All wides<transparent enum>: set", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  // No splat make yet
  W x {[](int, int) { return static_cast<E>(0); }};

  for( int i = 0; i != x.size(); ++i )
  {
    TTS_EQUAL(static_cast<E>(0), x.get(i));
    x.set(i, static_cast<E>(i + 1));
    TTS_EQUAL(static_cast<E>(i + 1), x.get(i));
  }
};

TTS_CASE_TPL("All wides<transparent struct>: set", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BS<E>;
  using W = typename Wb::template retype<S>;

  // No splat make yet
  W x {[](int, int) { return S::of(0); }};

  for( int i = 0; i != x.size(); ++i )
  {
    TTS_EQUAL(S::of(0), x.get(i));
    x.set(i, S::of(i + 1));
    TTS_EQUAL(S::of(i + 1), x.get(i));
  }
};

TTS_CASE_TPL("Make all wides<transparent enum>, splat", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<E>;

  W x { static_cast<E>(3) };

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && W::size() < min_n )
  {
    auto full_wide = eve::bit_cast(x, eve::as<eve::wide<E, eve::fixed<min_n>>> {});
    for( int i = 0; i != full_wide.size(); ++i )
    {
      E expected = static_cast<E>(i < Wb::size() ? 3 : 0);
      TTS_EQUAL(expected, full_wide.get(i));
    }
  }
};

TTS_CASE_TPL("Make all wides<transparent struct>, splat", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BS<E>;
  using W = typename Wb::template retype<S>;

  constexpr std::ptrdiff_t min_n = eve::fundamental_cardinal_v<E>;

  W x { S::of(3) };

  if constexpr( !eve::has_emulated_abi_v<decltype(x)> && W::size() < min_n )
  {
    auto full_wide = eve::bit_cast(x, eve::as<eve::wide<S, eve::fixed<min_n>>> {});
    for( int i = 0; i != full_wide.size(); ++i )
    {
      S expected = S::of(i < Wb::size() ? 3 : 0);
      TTS_EQUAL(expected, full_wide.get(i));
    }
  }
};

TTS_CASE_TPL("Slice all wides<transparent enum>", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  if constexpr( W::size() == 1 ) {
    TTS_PASS("Test passed");
  }
  else
  {
    W x {[](int i, int) { return static_cast<E>(i + 1); }};
    auto [l, h] = x.slice();

    int i = 0;
    for( ; i != W::size() / 2; ++i ) TTS_EQUAL(l.get(i), static_cast<E>(i + 1));
    for( ; i != W::size(); ++i ) TTS_EQUAL(h.get(i - (W::size() / 2)), static_cast<E>(i + 1));
  }
};

TTS_CASE_TPL("Slice all wides<transparent struct>", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BS<E>;
  using W = typename Wb::template retype<S>;

  if constexpr( W::size() == 1 ) {
    TTS_PASS("Test passed");
  }
  else
  {
    W x {[](int i, int) { return S::of(i + 1); }};
    auto [l, h] = x.slice();

    int i = 0;
    for( ; i != W::size() / 2; ++i ) TTS_EQUAL(l.get(i), S::of(i + 1));
    for( ; i != W::size(); ++i ) TTS_EQUAL(h.get(i - (W::size() / 2)), S::of(i + 1));
  }
};
