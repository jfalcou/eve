//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return min(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return min(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::min, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::min, a, b);
        }
        else
        {
          return if_else(is_less(b, a), b, a);
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::min] - Incompatible types.");
        return {};
      }
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE  auto min_( EVE_SUPPORTS(cpu_),
                              logical<T> const &a, logical<U> const &b
                            ) noexcept
  requires( logical<T>,
            Vectorized<T>, Vectorized<U>,
            EqualCardinal<T,U>
          )
  {
    return logical_and(a, b); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic
  template<typename T, typename U>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &v0
                            , U const &v1) noexcept
  requires( as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr(std::is_integral_v<T>)
      return eve::min(v0, v1);
    else
      return if_else(is_nan(v1), v0, eve::min(v0, v1));
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE  auto min_( EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , logical<T> const &a
                            , logical<U> const &b
                            ) noexcept
  requires( logical<T>,
            Vectorized<T>, Vectorized<U>,
            EqualCardinal<T,U>
          )
  {
    return logical_and(a, b); 
  }
  
}

#endif
