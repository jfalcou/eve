//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SIGNNZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/forward.hpp>
#include <eve/platform.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto signnz_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return if_else(is_nan(a), eve::allbits_, bit_or(One(as(a)), bitofsign(a)));
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return bit_or(shr(a, (sizeof(T) * 8 - 1)), One(as(a)));
      else
        return One(as(a));
    }
  }
  
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto signnz_(EVE_SUPPORTS(cpu_)
                              , pedantic_type const &
                              , wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(eve::platform::supports_invalids)
      {
        return if_else(is_nan(a), eve::allbits_, signnz(a));
      }
      else
      {
        return signnz(a); 
      }
    } 
  }
}

#endif
