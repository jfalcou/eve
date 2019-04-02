//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_LOGICAL_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_LOGICAL_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>
  logical_and_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(!std::is_same_v<T,U>)
      {
        static_assert( std::is_same_v<T,U>, "[eve::logical_and] - Incompatible types.");
        return {};
      }
      else
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::logical_and, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::logical_and, a, b);
        }
        else
        {
          return bitwise_cast<as_logical_t<T>>( bitwise_and(bitwise_mask(a), bitwise_mask(b)) );
        }
      }
    }
    else if constexpr( is_vectorized_v<T> && !is_vectorized_v<U> )
    {
      return logical_and(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> && is_vectorized_v<U> )
    {
      return logical_and(U{a},b);
    }
    else
    {
      if constexpr(!is_logical_v<T> && !is_logical_v<U>)
      {
        return a && b;
      }
      else if constexpr(is_logical_v<T> && !is_logical_v<U>)
      {
        return a.value() && b;
      }
      else if constexpr(is_logical_v<T> && !is_logical_v<U>)
      {
        return a && b.value();
      }
      else
      {
        return a.value() && b.value();
      }
    }
  }
}

#endif
