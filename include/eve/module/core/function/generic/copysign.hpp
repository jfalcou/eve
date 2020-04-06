//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_COPYSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_COPYSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/signnz.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto copysign_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U> && signed_value<T>
  {
    return arithmetic_call(copysign, a, b); 
  }
  
  template<floating_real_value T>
  EVE_FORCEINLINE  T copysign_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    if constexpr(native<T>)
    {
      return bit_or(bitofsign(b), bit_notand(Signmask(as(a)), a));
    }
    else return apply_over(copysign, a, b);
  }  
}

#endif
