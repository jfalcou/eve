//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BINARIZE_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BINARIZE_NOT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/logical.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_not.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto  binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           ) noexcept
  {
    return  bit_andnot(One<T>(),cond.bits());
  }

  template<real_value T, real_scalar_value U>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , U const & val
                           ) noexcept
  {
      return  bit_andnot(T(val),cond.bits());
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_object<eve::tag::allbits_, void, void> const &
                           ) noexcept
  {
    return bit_not(cond.mask());
  }

  template<real_value T>
  EVE_FORCEINLINE auto binarize_not_(EVE_SUPPORTS(cpu_)
                           , logical<T> const &cond
                           , callable_object<eve::tag::mone_, void, void> const &
                           ) noexcept
  {
    if constexpr(integral_value<T>) return  bit_not(cond.mask());
    else                            return  eve::binarize_not(cond,Mone<value_type_t<T>>());
  }

}

#endif
