//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_INDEG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_INDEG_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/fma.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto indeg_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
 {
   if constexpr(native<T>)
   {
     auto radindeg  = Ieee_constant<T, 0X42652EE1U, 0X404CA5DC1A63C1F8ULL>();
     auto radindegr = Ieee_constant<T, 0X353387C0U, 0X3CE1E7AB456405F8ULL>();
     return fma(a, radindegr, a*radindeg);
   }
   else return apply_over(indeg, a);
 }

}

#endif
