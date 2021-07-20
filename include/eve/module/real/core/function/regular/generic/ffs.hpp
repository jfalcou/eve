//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/countl_zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE constexpr T ffs_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      auto z = T(a0&-a0);
      return T((sizeof(elt_t)*8-1)-countl_zero(z));
    }
    else return apply_over(ffs, a0);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_value U>
  EVE_FORCEINLINE auto ffs_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, ffs, t);
  }
}
