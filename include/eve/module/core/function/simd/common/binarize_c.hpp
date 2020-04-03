//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BINARIZE_C_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BINARIZE_C_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE
  wide<T, N, ABI> binarize_c_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &cond
                           ) noexcept
  {
    using t_t = wide<T, N, ABI>;
    return  bit_andnot(One<t_t>(),cond.bits());
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE
  wide<T, N, ABI> binarize_c_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &cond
                           , U const & val
                           ) noexcept
  {
    if constexpr(is_Vectorizable_v<U>)
    {
      using t_t = wide<T, N, ABI>;
      return  bit_andnot(t_t(val),cond.bits());
    }
    else if constexpr(std::is_same_v<U, eve::detail::callable_object<eve::tag::allbits_, void, void>)
    {
      return bit_not(cond.mask());
    }
    else if constexpr(std::is_same_v<U, eve::detail::callable_object<eve::tag::mone_, void, void>)
    {
      if constexpr(std::is_integral_v<T>) return  bit_not(cond.mask());
      else return  binarize_c(cond,eve::Mone<T>());
    }
    return wide<T, N, ABI>();
  }
}

#endif
