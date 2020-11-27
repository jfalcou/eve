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
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <tuple>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto two_split_(EVE_SUPPORTS(cpu_)
                                 , const T& a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      T const c = Ieee_constant<T, 0x46000000U, 0x41a0000000000000ULL>()*a;
      T const c1 = c-a;
      T r0 = c-c1;
      return std::make_tuple(r0, a-r0);
    }
    else return apply_over2(two_split, a);
  }
}

