//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SIND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SIND_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_)
                                     , D const &
                                     , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      const T inv180 = T(5.5555555555555555555555555555555555555555555555555e-3);
      return D()(sinpi)(a0*inv180);
    }
    else return apply_over(D()(sind), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  {
    return sind(regular_type(), a0);
  }

}

#endif
