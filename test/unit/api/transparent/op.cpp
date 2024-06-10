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

enum class E: uint32_t { };

TTS_CASE_TPL("Wide<transparent enum> eq/neq", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  W x{ static_cast<E>(3) };
  W y{ static_cast<E>(2) };

  TTS_EQUAL(x, x);
  TTS_NOT_EQUAL(x, y);
  TTS_EQUAL((x != static_cast<E>(0)), (y != static_cast<E>(0)));
};

TTS_CASE_TPL("Wide<transparent struct> eq/neq", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BS<E>;
  using W = typename Wb::template retype<S>;

  W x{ S::of(3) };
  W y{ S::of(2) };

  TTS_EQUAL(x, x);
  TTS_NOT_EQUAL(x, y);
  TTS_EQUAL((x != S::of(0)), (y != S::of(0)));
};
