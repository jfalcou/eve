//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/branch.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_)
                               , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T> && integral_value<T>) return T(~v);
      else                                               return eve::bit_xor(v, allbits(eve::as(v)));
    }
    else return apply_over(bit_not, v);
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::bit_not, t);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<real_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator~(wide<T, N, ABI> const &v) noexcept
  -> decltype(bit_not(v))
  {
    return bit_not(v);
  }
}
