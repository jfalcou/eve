//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ONEMINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ONEMINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto oneminus_(EVE_SUPPORTS(cpu_),
                                 wide<T, N, ABI> const &v) noexcept
  {
    return One(as(v))-v;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto oneminus_(EVE_SUPPORTS(cpu_)
                                , saturated_type const &
                                , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) return oneminus(v);
    else if constexpr(std::is_signed_v<T>)
    {
      return if_else(v < Valmin(as(v))+2, Valmax(as(v)), oneminus(v));
    }
    else // if constexpr(std::is_unsigned_v<T>)
    {
      return if_else(v > One(as(v)), eve::zero_, oneminus(v));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , U const & cond
                                          , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(!is_Vectorized_v<U>)
      return cond ? oneminus(v) : v;
    else
      return if_else(cond, One(as(v))-v, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked Saturated case
  template<typename U, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , U const & cond
                                          , saturated_type const &
                                          , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(!is_Vectorized_v<U>)
      return cond ? saturated_(oneminus)(v) : v;
    else
      return if_else(cond, saturated_(oneminus)(v), v);
  }

}

#endif
