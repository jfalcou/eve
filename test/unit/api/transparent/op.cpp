//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/arch/wide.hpp>

#include <iostream>

using namespace eve;

// base struct used in the test
template <typename E>
struct BS {
  eve::element_type_t<E> value;

  template <typename V>
  static BS of(V v) { return BS{ static_cast<E>(v) }; }
};

template<typename E>
struct eve::transparent_trait<BS<E>> { using type = E; };

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of arithmetic operators on wide", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  using i_t = eve::element_type_t<Wb>;
  enum class E: i_t { };
  using T = typename Wb::template retype<E>;

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

  TTS_EXPR_IS((T() == T())                  , logical<T>);
  TTS_EXPR_IS((T() != T())                  , logical<T>);
  TTS_EXPR_IS((T() <  T())                  , logical<T>);
  TTS_EXPR_IS((T() <= T())                  , logical<T>);
  TTS_EXPR_IS((T() >  T())                  , logical<T>);
  TTS_EXPR_IS((T() >= T())                  , logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<T>()), logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<T>()), logical<T>);

  TTS_EXPR_IS((T() == v)                  , logical<T>);
  TTS_EXPR_IS((T() != v)                  , logical<T>);
  TTS_EXPR_IS((T() <  v)                  , logical<T>);
  TTS_EXPR_IS((T() <= v)                  , logical<T>);
  TTS_EXPR_IS((T() >  v)                  , logical<T>);
  TTS_EXPR_IS((T() >= v)                  , logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<E>()), logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<E>()), logical<T>);

  TTS_EXPR_IS((v == T())                  , logical<T>);
  TTS_EXPR_IS((v != T())                  , logical<T>);
  TTS_EXPR_IS((v <  T())                  , logical<T>);
  TTS_EXPR_IS((v <= T())                  , logical<T>);
  TTS_EXPR_IS((v >  T())                  , logical<T>);
  TTS_EXPR_IS((v >= T())                  , logical<T>);
  TTS_EXPR_IS((logical<E>() != logical<T>()), logical<T>);
  TTS_EXPR_IS((logical<E>() != logical<T>()), logical<T>);

  if constexpr( eve::integral_element_value<T> )
  {
    TTS_EXPR_IS( T() % T(), T);
    TTS_EXPR_IS( v % T(), T);
    TTS_EXPR_IS( T() % v, T);
  }
};

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

TTS_CASE_TPL("Wide<transparent struct> eq/neq", eve::test::simd::all_types)
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