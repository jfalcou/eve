//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto mul_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
                            requires( std::conditional_t<is_vectorized_v<T>,T,U>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
                                    )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return mul(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return mul(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::mul, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::mul, a, b);
        }
        else
        {
          static_assert( wrong<T,U>, "[eve::mul] - Unsupported ABI.");
          return {};
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::mul] - Incompatible types.");
        return {};
      }
    }
  }
}

#endif
