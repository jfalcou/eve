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
#include <eve/function/is_nez.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/is_logical.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_)
                               , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(is_logical_v<T>) return v.mask();
      else                          return is_nez(v).mask();
    }
    else                            return apply_over(bit_mask, v);
  }

}

