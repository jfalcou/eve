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
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto signnz_(EVE_SUPPORTS(simd_)
                            ,wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      #ifndef BOOST_SIMD_NO_NANS
      return if_else( is_nan(a), eve::allbits_, bitwise_or(One(as(a)), bitwise_and(Signmask(as(a)), a)));
      #else
      return bitwise_or(One(as(a)), bitwise_and(Signmask(as(a)), a));
      #endif
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return bitwise_or(shr(a, (sizeof(T)*8-1)), One(as(a)));
      else
        return One(as(a)); 
      
    }   
  }
}

#endif
