//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_LESSGREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_LESSGREATER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/function/is_ordered.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto is_lessgreater_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return is_lessgreater(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return is_lessgreater(U{a},b);
    }
    else
    {
      if constexpr( std::is_same_v<T, U> )
      {
        if constexpr(std::is_integral_v<typename T::value_type>)
        {
          return is_not_equal(a, b);
        }
        else
        {
          return logical_and(is_not_equal(a, b), is_ordered(a, b));
        }
      }
      else
      {
        
        static_assert( std::is_same_v<T,U>, "[eve::is_lessgreater] - Incompatible types.");
      }
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE  auto is_lessgreater_( EVE_SUPPORTS(cpu_),
                                         logical<T> const &v0, logical<U> const &v1
                                       ) noexcept
  requires( logical<T>,
            Vectorized<T>, Vectorized<U>,
            EqualCardinal<T,U>
          )
  {
    return is_not_equal(v0, v1);
  }
}

#endif
