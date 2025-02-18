//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>

namespace eve::detail
{
  template<typename T, typename Op> struct has_equal_lambda
  {
    Op op;
    T  v;

    has_equal_lambda(Op o, T p) : op(o), v(p) {}
    EVE_FORCEINLINE auto operator()(auto x) const { return op(v, x); }
  };

  template<callable_options O, simd_value T, simd_value U>
  EVE_FORCEINLINE auto has_equal_in_(EVE_REQUIRES(cpu_), O const&, T x, U match_against, auto pred)
  {
    // For now assuming that the compiler can interleave these operations
    auto all_pos = try_each_group_position(match_against, eve::lane<1>);
    auto tests   = kumi::map(has_equal_lambda { pred, x }, all_pos);
    return kumi::fold_left(eve::logical_or, tests);
  }
}
