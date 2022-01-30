//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto  binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return  bit_andnot(one(eve::as<T>()),cond.bits());
    }
    else return  apply_over(binarize_not, cond);
  }

  template<real_value T, real_scalar_value U>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , U const & val
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return if_else(cond, zero(as(val)), val);
    }
    else return  apply_over(binarize_not, cond, val);
  }

  template<real_value T, real_scalar_value U>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                                    , logical<T> const &cond
                                    , eve::as<U> const &
                                    ) noexcept
  {
    using R = eve::as_wide_t<U, eve::cardinal_t<T>>;
    return if_else(cond, zero, one(as<R>()));
  }

   template<real_value T>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_allbits_ const &
                           ) noexcept
  {
    return bit_not(cond.mask());
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_mone_ const &
                           ) noexcept
  {
    if constexpr(integral_value<T>) return  bit_not(cond.mask());
    else                            return  eve::binarize_not(cond,mone(eve::as<element_type_t<T>>()));
  }

}
