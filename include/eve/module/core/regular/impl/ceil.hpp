//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T ceil_(EVE_SUPPORTS(cpu_)
                                   , T const &a0) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      T z = eve::trunc(a0);
      return inc[ z < a0 ](z);
    }
    else return apply_over(ceil, a0);
  }

  ////////////////////////////////////////////////////////////////////////////////////
  // return integral types

  template<integral_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto ceil_(EVE_SUPPORTS(cpu_), D const &, T xx) noexcept
  requires(is_one_of<D>(types<int_converter, uint_converter>{}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      return D()(ceil(xx));
    }
    else
    {
      return apply_over(D()(ceil), xx);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto ceil_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::ceil, t);
  }
}
