//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/conditional.hpp>

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

// Returns clear sve_true for type of a given cardinal
// while masking potential garbage value
template<relative_conditional_expr C, typename T>
EVE_FORCEINLINE svbool_t
sve_true(C cond, as<T> tgt)
{
  if constexpr(C::is_complete && C::is_inverted)
  {
    using v_t   = element_type_t<T>;
    using ec_t  = expected_cardinal_t<v_t, typename T::abi_type>;
    return keep_first(T::size()).mask(as<as_wide_t<v_t,ec_t>>{});
  }
  else
  {
    return cond.mask(tgt);
  }
}
}
