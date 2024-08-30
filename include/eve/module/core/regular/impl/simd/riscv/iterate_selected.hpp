//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/count_true.hpp>

namespace eve::detail
{

template<callable_options O, typename L, typename F>
EVE_FORCEINLINE bool
iterate_selected_(EVE_REQUIRES(rvv_), O const& opts, top_bits<L> l, F&& f)
requires(L::size() >= 64)
{
  auto [lo, hi] = l.slice();
  if( iterate_selected(lo, f) ) return true;
  return iterate_selected(hi, detail::plus_offset_lambda<F> {f, L::size() / 2});
}

}
