//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{

template<eve::arithmetic_simd_value T>
EVE_FORCEINLINE T
iota_(EVE_REQUIRES(cpu_), eve::callable_options auto const& opts, as<T> tgt)
{
  const auto cx = opts[condition_key];
  using C       = decltype(cx);

  if constexpr( C::is_complete && C::is_inverted ) return T {[](int i, int) { return i; }};
  else if constexpr( !C::has_alternative ) return iota[cx.else_(eve::zero(tgt))](tgt);
  else return mask_op(cx, iota, tgt);
}
}
