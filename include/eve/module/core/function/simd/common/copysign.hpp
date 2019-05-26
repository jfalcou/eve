//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/signnz.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto copysign_(EVE_SUPPORTS(simd_)
                                , wide<T, N, ABI> const &a0
                                , wide<T, N, ABI> const &a1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
      return bitwise_or(bitofsign(a1), bitwise_notand(Signmask(as(a0)), a0));
    else
    {
      if constexpr(std::is_unsigned_v<T>)
        return  a0; 
      else
        return if_else(a0 == Valmin(as(a0)) && is_ltz(a1), Valmax(as(a0)), eve::abs(a0)*signnz(a1)); 
    }
  }
}

#endif
