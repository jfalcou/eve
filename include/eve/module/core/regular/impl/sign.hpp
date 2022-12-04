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
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/binarize.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE T
sign_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_eqz(a) ) return a;
      if constexpr( signed_value<T> )
      {
        T r = bool(is_gtz(a)) - bool(is_ltz(a));
        if constexpr( eve::platform::supports_nans && floating_value<T> )
        {
          return is_nan(a) ? a : r;
        }
        else { return r; }
      }
      else if constexpr( unsigned_value<T> ) { return binarize(is_nez(a)); }
    }
    else if constexpr( simd_value<T> )
    {
      if constexpr( signed_value<T> )
      {
        T r = if_else(is_eqz(a), a, binarize(is_gtz(a)) - binarize(is_ltz(a)));
        if constexpr( eve::platform::supports_nans && floating_value<T> )
        {
          return if_else(is_nan(a), eve::allbits, r);
        }
        else { return r; }
      }
      else if constexpr( unsigned_value<T> ) { return binarize(is_nez(a)); }
    }
  }
  else { return apply_over(sign, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
sign_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, sign, t);
}
}
