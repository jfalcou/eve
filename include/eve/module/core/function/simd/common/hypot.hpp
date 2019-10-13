//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto hypot_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>,
            Floating<value_type_t<T>>,
            Floating<value_type_t<U>>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return hypot(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return hypot(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<abi_type_t<T>>) { return aggregate(eve::hypot, a, b); }
        else if constexpr(is_emulated_v<abi_type_t<T>>)
        {
          return map(eve::hypot, a, b);
        }
        else
        {
          return eve::sqrt(fma(a, a, sqr(b)));
        }
      }
    }
  }
}

#endif
