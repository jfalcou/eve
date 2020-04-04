//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_MASK_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/detail/branch.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/is_logical.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_)
                               , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(is_logical_v<T>) return v.mask();
      else                          return is_nez(v).mask();
    }
    else                            return apply_over(bit_mask, v); 
  }

}

#endif
