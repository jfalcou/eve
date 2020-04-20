//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CSC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CSC_HPP_INCLUDED


#include <eve/detail/implementation.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T, typename D>
  EVE_FORCEINLINE auto csc_(EVE_SUPPORTS(cpu_)
                           ,  D const &
                            , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>) return rec(D()(sin)(a0));
    else                    return apply_over(D()(csc), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto csc_(EVE_SUPPORTS(cpu_)
                            , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>) return rec(sin(a0));
    else                    return apply_over(csc, a0);

  }
}

#endif
