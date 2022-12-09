//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr T
ceil_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( integral_value<T> ) return a0;
  else if constexpr( has_native_abi_v<T> )
  {
    T z = eve::trunc(a0);
    return inc[z < a0](z);
  }
  else return apply_over(ceil, a0);
}

////////////////////////////////////////////////////////////////////////////////////
// return integral types

template<integral_value T, typename D>
EVE_FORCEINLINE constexpr auto
ceil_(EVE_SUPPORTS(cpu_), D const&, T xx) noexcept
    requires(is_one_of<D>(types<int_converter, uint_converter> {}))
{
  if constexpr( has_native_abi_v<T> ) { return D()(ceil(xx)); }
  else { return apply_over(D()(ceil), xx); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value T>
EVE_FORCEINLINE auto
ceil_(EVE_SUPPORTS(cpu_), C const& cond, T const& a) noexcept
{
  return mask_op(cond, eve::ceil, a);
}
}
