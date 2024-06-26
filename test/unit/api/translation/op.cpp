//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/arch/wide.hpp>

using namespace eve;

// base struct used in the test
template <typename E>
struct BaseStruct {
  E value;

  template <typename V>
  static BaseStruct of(V v) { return BaseStruct{ static_cast<E>(v) }; }
};

template<typename E>
struct eve::translation_of<BaseStruct<E>> { using type = E; };

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of arithmetic operators on wide<translated enum>", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using i_t = eve::element_type_t<Wb>;
  enum class E: i_t { };
  using T = typename Wb::template retype<E>;
  using L = as_logical_t<T>;
  using l_e = as_logical_t<E>;

  auto v = T{};

  TTS_EXPR_IS( T()    + T()   , T);
  TTS_EXPR_IS( T()    - T()   , T);
  TTS_EXPR_IS( T()    * T()   , T);
  TTS_EXPR_IS( T()    / T()   , T);
  TTS_EXPR_IS( T()    + v , T);
  TTS_EXPR_IS( v  + T()   , T);
  TTS_EXPR_IS( T()    - v , T);
  TTS_EXPR_IS( v  - T()   , T);
  TTS_EXPR_IS( T()    * v , T);
  TTS_EXPR_IS( v  * T()   , T);
  TTS_EXPR_IS( T()    / v , T);
  TTS_EXPR_IS( v  / T()   , T);

  TTS_EXPR_IS( T()    & T()   , T);
  TTS_EXPR_IS( T()    & v , T);
  TTS_EXPR_IS( v  & T()   , T);
  TTS_EXPR_IS( T()    | T()   , T);
  TTS_EXPR_IS( T()    | v , T);
  TTS_EXPR_IS( v  | T()   , T);
  TTS_EXPR_IS( T()    ^ T()   , T);
  TTS_EXPR_IS( T()    ^ v , T);
  TTS_EXPR_IS( v  ^ T()   , T);
  TTS_EXPR_IS( ~T()           , T);

  TTS_EXPR_IS((T() == T())                  , L);
  TTS_EXPR_IS((T() != T())                  , L);
  TTS_EXPR_IS((T() <  T())                  , L);
  TTS_EXPR_IS((T() <= T())                  , L);
  TTS_EXPR_IS((T() >  T())                  , L);
  TTS_EXPR_IS((T() >= T())                  , L);
  TTS_EXPR_IS((L() == L()), L);
  TTS_EXPR_IS((L() != L()), L);

  TTS_EXPR_IS((T() == v)                  , L);
  TTS_EXPR_IS((T() != v)                  , L);
  TTS_EXPR_IS((T() <  v)                  , L);
  TTS_EXPR_IS((T() <= v)                  , L);
  TTS_EXPR_IS((T() >  v)                  , L);
  TTS_EXPR_IS((T() >= v)                  , L);
  TTS_EXPR_IS((L() == l_e()), L);
  TTS_EXPR_IS((L() != l_e()), L);

  TTS_EXPR_IS((v == T())                  , L);
  TTS_EXPR_IS((v != T())                  , L);
  TTS_EXPR_IS((v <  T())                  , L);
  TTS_EXPR_IS((v <= T())                  , L);
  TTS_EXPR_IS((v >  T())                  , L);
  TTS_EXPR_IS((v >= T())                  , L);
  TTS_EXPR_IS((l_e() == L()), L);
  TTS_EXPR_IS((l_e() != L()), L);

  if constexpr( eve::integral_element_value<T> )
  {
    TTS_EXPR_IS( T() % T(), T);
    TTS_EXPR_IS( v % T(), T);
    TTS_EXPR_IS( T() % v, T);
  }
};

//==================================================================================================
// Op tests
//==================================================================================================
TTS_CASE_TPL("Wide<translated enum> eq/neq", eve::test::simd::integers)
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

TTS_CASE_TPL("Wide<translated struct> eq/neq", eve::test::simd::all_types)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BaseStruct<E>;
  using W = typename Wb::template retype<S>;

  W x{ S::of(3) };
  W y{ S::of(2) };

  TTS_EQUAL(x, x);
  TTS_NOT_EQUAL(x, y);
  TTS_EQUAL((x != S::of(0)), (y != S::of(0)));
};

TTS_CASE_TPL("Wide<translated enum> add", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  W x{ static_cast<E>(2) };
  W y{ static_cast<E>(4) };

  TTS_EQUAL(x + static_cast<E>(2), y);
  x += static_cast<E>(2);
  TTS_EQUAL(x, y);
};

TTS_CASE_TPL("Wide<translated struct> add", eve::test::simd::all_types)
<typename Wb>(tts::type<Wb>)
{
  using E = eve::element_type_t<Wb>;
  using S = BaseStruct<E>;
  using W = typename Wb::template retype<S>;

  W x{ S::of(2) };
  W y{ S::of(4) };

  TTS_EQUAL(x + S::of(2), y);
  x += S::of(2);
  TTS_EQUAL(x, x);
};
