//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BINARIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BINARIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE
  wide<T, N, ABI> binarize_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &cond
                           ) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    return  bitwise_and(One<t_t>(),cond.bits());
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE 
  wide<T, N, ABI> binarize_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &cond
                           , U const & val 
                           ) noexcept
  {
    if constexpr(is_vectorizable_v<U>)
    {
      using t_t = wide<T, N, ABI>; 
      return  bitwise_and(t_t(val),cond.bits());
    }
    else if constexpr(std::is_same_v<U, eve::callable_allbits_>)
    {
       return cond.mask();
    }
    else if constexpr(std::is_same_v<U, eve::callable_mone_>)
    {
      if constexpr(std::is_integral_v<T>) return  cond.mask();
      else return  binarize(cond,eve::Mone<T>());
    }
    return wide<T, N, ABI>(); 
  }
}

#endif
