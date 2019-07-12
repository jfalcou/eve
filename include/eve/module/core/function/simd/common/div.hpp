//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
                            requires( std::conditional_t<is_vectorized_v<T>,T,U>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
                                    )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return div(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return div(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::div, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::div, a, b);
        }
        else
        {
          if constexpr( std::is_floating_point_v<T> )
          {
            return mul(a,rec(b));
          }
          else
          {
            return map( eve::div, a, b);
          }
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::div] - Incompatible types.");
        return {};
      }
    }
  }
}

#endif

#include <eve/module/core/function/simd/common/if_div.hpp>
