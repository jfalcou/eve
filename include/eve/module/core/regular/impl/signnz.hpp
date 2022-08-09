//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE T
signnz_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( unsigned_value<T> ) { return one(eve::as(a)); }
    else if constexpr( floating_value<T> ) { return bit_or(one(eve::as(a)), bitofsign(a)); }
    else if constexpr( signed_value<T> )
    {
      using elt_t = element_type_t<T>;
      return (a >> (sizeof(elt_t) * 8 - 2)) | T(1);
    }
  }
  else { return apply_over(signnz, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
signnz_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, signnz, t);
}
}
