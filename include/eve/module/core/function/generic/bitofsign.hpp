//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BITOFSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BITOFSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bitofsign_(EVE_SUPPORTS(cpu_)
                                 , T const &a) noexcept
  {
        if constexpr(native<T>) return bit_and(a, Signmask(as(a)));
        else                    return apply_over(bitofsign, a);
  }
}

#endif
