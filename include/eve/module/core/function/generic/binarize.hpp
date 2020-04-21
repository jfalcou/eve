//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BINARIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BINARIZE_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/logical.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bit_and.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto  binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return  bit_and(One<T>(),cond.bits());
    }
    else return  apply_over(binarize, cond);
  }

  template<real_value T, real_scalar_value U>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , U const & val
                           ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return  bit_and(T(val),cond.bits());
    }
    else return  apply_over(binarize, cond, val);
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_object<eve::tag::allbits_, void, void> const &
                           ) noexcept
  {
    return cond.mask();
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_object<eve::tag::mone_, void, void> const &
                           ) noexcept
  {
//     if constexpr(has_native_abi_v<T>)
//     {
      if constexpr(integral_value<T>) return  cond.mask();
      else                            return  eve::binarize(cond,Mone<value_type_t<T>>());
//     }
//     else return  apply_over(binarize, cond, eve::mone_);
  }
}

#endif
