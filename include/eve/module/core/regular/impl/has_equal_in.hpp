//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/try_each_group_position.hpp>

namespace eve::detail
{

template<simd_value T, simd_value U>
EVE_FORCEINLINE auto
has_equal_in_(EVE_SUPPORTS(cpu_), T x, U match_against)
{
  return has_equal_in(x, match_against, is_equal);
}

template<typename Op, typename T> struct has_equal_lambda
{
  Op op;
  T  v;

  has_equal_lambda(Op op, T v) : op(op), v(v) {}

  EVE_FORCEINLINE auto operator()(auto x) const { return op(v, x); }
};

// kumi/issues/71 : tuple reduce

template<typename T, typename Op> struct reduce_lambda
{
  T  sum;
  Op op;

  reduce_lambda(T sum, Op op) : sum(sum), op(op) {}

  EVE_FORCEINLINE
  friend reduce_lambda operator+(reduce_lambda self, T x) {
    self.sum = self.op(self.sum, x);
    return self;
  }
};

template<std::size_t... i>
EVE_FORCEINLINE auto
reduce_tuple_impl(auto x, std::index_sequence<0, i...>, auto op)
{
  return ( reduce_lambda{kumi::get<0>(x), op} + ... + kumi::get<i>(x) ).sum;
}

template<typename ...Ts>
EVE_FORCEINLINE auto
reduce_tuple(kumi::tuple<Ts...> x, auto op) {
  return reduce_tuple_impl(x, std::index_sequence_for<Ts...>{}, op);
}

template<simd_value T, simd_value U>
EVE_FORCEINLINE auto
has_equal_in_(EVE_SUPPORTS(cpu_), T x, U match_against, auto pred)
{
  // For now assuming that the compiler can interleave these operations
  auto all_pos = try_each_group_position(match_against, eve::lane<1>);
  auto tests   = kumi::map(has_equal_lambda {pred, x}, all_pos);
  return reduce_tuple(tests, eve::logical_or);
}

}
