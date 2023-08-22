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
#include <eve/arch/fundamental_cardinal.hpp>

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
EVE_FORCEINLINE T
sve_true(C cond, as<T> tgt)
{
  if constexpr(C::is_complete && C::is_inverted)
  {
    using v_t   = element_type_t<T>;
    using fc_t  = fundamental_cardinal_t<v_t>;

    if constexpr ( eve::has_aggregated_abi_v<T> )
    {
      using half_t = as_wide_t<v_t, eve::fixed<T::size() / 2>>;
      half_t half = sve_true(cond, eve::as<half_t>{});
      return T{half, half};
    }
    else if constexpr(T::size() == fc_t::value )      return sve_true<v_t>();
    else return bit_cast(keep_first(T::size()).mask(as<as_wide_t<v_t, fc_t>>{}), tgt);
  }
  else
  {
    return cond.mask(tgt);
  }
}
}
