//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>
#ifndef EVE_NO_NANS
#include <eve/function/is_nan.hpp>
#include <eve/constant/allbits.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto sign_(EVE_SUPPORTS(cpu_)
                            ,wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto r = if_else[as(a)](is_gtz(a), eve::one_, eve::zero_)
               -if_else[as(a)](is_ltz(a), eve::one_, eve::zero_);
#ifdef EVE_NO_NANS
      return r;
#else
      return if_else(is_nan(a), eve::allbits_, r);
#endif
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return if_else[as(a)](is_gtz(a), eve::one_, eve::zero_)
               -if_else[as(a)](is_ltz(a), eve::one_, eve::zero_);
      else
      {
        return if_else[as(a)](a, eve::one_, eve::zero_);
      }
    }   
  }
}

#endif
