//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FRAC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FRAC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T>
  EVE_FORCEINLINE auto frac_(EVE_SUPPORTS(cpu_)
                            , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(floating_value<T>) return a - trunc(a);
      else return Zero(as(a));
    }
    else return apply_over(frac, a);
  }
}

#endif
