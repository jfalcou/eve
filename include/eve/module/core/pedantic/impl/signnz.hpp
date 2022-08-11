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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE T
signnz_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( unsigned_value<T> ) { return one(eve::as(a)); }
    else if constexpr( floating_value<T> )
    {
      auto r = bit_or(one(eve::as(a)), bitofsign(a));
      if constexpr( eve::platform::supports_nans )
      {
        if constexpr( scalar_value<T> ) { return is_nan(a) ? a : r; }
        else { return if_else(is_nan(a), eve::allbits, r); }
      }
      else { return r; }
    }
    else if constexpr( signed_value<T> )
    {
      using elt_t = element_type_t<T>;
      return (a >> (sizeof(elt_t) * 8 - 2)) | T(1);
    }
  }
  else { return apply_over(pedantic(signnz), a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
signnz_(EVE_SUPPORTS(cpu_), C const& cond, pedantic_type const&, U const& t) noexcept
{
  return mask_op(cond, pedantic(signnz), t);
}
}
