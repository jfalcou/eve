//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/half.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto average_(EVE_SUPPORTS(cpu_)
                                , T const &a
                                , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return average(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return average(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::average, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::average, a, b);
        }
        else
        {
          if constexpr(std::is_integral_v<typename T::value_type>)
             return bitwise_and(a, b)+shr(bitwise_xor(a, b),1);
          else
            return fma(a,Half<T>(),b*Half<T>()); 
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::average] - Incompatible types.");
        return {};
      }
    }
  }
  
}

#endif
