//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CLAMP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CLAMP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto clamp_(EVE_SUPPORTS(cpu_), T const &x, U const &lo, V const &hi) noexcept
  requires( T, vectorized<T> )
  {
    if constexpr( !is_vectorized_v<U> || !is_vectorized_v<V>)
    {
      return clamp(x, abi_cast<T>(lo), abi_cast<T>(hi));
    }
    else
    {
      using abi_t = typename T::abi_type;
      if constexpr(is_emulated_v<abi_t>)
      {
        return map(eve::clamp, x, lo, hi);
      }
      else if constexpr(is_aggregated_v<abi_t>)
      {
        return aggregate(eve::clamp, x, lo, hi);
      }
      else
      {
        return eve::min(eve::max(x, lo), hi);
      }
      return T();
    }
  }
}

#endif
