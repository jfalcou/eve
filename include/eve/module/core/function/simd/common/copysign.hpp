//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/function/is_gtz.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_notand.hpp>
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
  template<typename T, typename U>
  EVE_FORCEINLINE auto copysign_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>, T, U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>,
            same_as<value_type_t<T>, value_type_t<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::copysign, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::copysign, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_Vectorized_v<T> & is_Vectorized_v<U>)
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(std::is_floating_point_v<value_type_t<T>>)
        {
          return bit_or(bitofsign(b), bit_notand(Signmask(as(a)), a));
        }
        else
        {
          if constexpr(std::is_unsigned_v<value_type_t<T>>)
          {
            return a;
          }
          else
          {
            return if_else(a == Valmin(as(a)) && is_gtz(b), Valmax(as(a)), eve::abs(a) * signnz(b));
          }
        }
      }
    }
    else // if constexpr( is_Vectorized_v<T> ^ is_Vectorized_v<U> )
    {
      return eve::copysign(abi_cast<U>(a), abi_cast<T>(b));
    }
  }
}

#endif
