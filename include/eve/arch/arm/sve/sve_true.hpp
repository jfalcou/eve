//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>

namespace eve::detail
{

// Returns clear sve_true for type
// Calling svptrue_b8 is OK for most cases, where you OK with
// 1s in insignificant bits but sometimes you are not.
template<typename T>
EVE_FORCEINLINE svbool_t
sve_true()
{
  if constexpr( sizeof(T) == 1 ) return svptrue_b8();
  else if constexpr( sizeof(T) == 2 ) return svptrue_b16();
  else if constexpr( sizeof(T) == 4 ) return svptrue_b32();
  else if constexpr( sizeof(T) == 8 ) return svptrue_b64();
}

// Generate optimized mask that takes ignore_none into account
template<conditional_expr C, typename T>
EVE_FORCEINLINE auto
sve_ignore_hidden_mask(C cond, as<T> tgt) noexcept
{
  if constexpr(C::is_complete && C::is_inverted) return sve_true<T>();
  else return cond.mask(tgt);
}
} // namespace eve::detail
