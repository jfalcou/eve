//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_less.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_not_greater_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
                            requires( as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
                                    )
  {
    if constexpr( is_vectorized_v<T> && !is_vectorized_v<U> )
    {
      return is_not_greater_equal(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> && is_vectorized_v<U> )
    {
      return is_not_greater_equal(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( std::is_floating_point_v<typename T::value_type> )
        {
          return logical_not(is_greater_equal(a,b));
        }
        else
        {
          return is_less(a,b);
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::is_not_greater_equal] - Incompatible types.");
        return {};
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_not_greater_equal_( EVE_SUPPORTS(cpu_),
                                            logical<T> const &a, logical<U> const &b
                                          ) noexcept
                            requires( logical<T>,
                                      Vectorized<T>, Vectorized<U>,
                                      EqualCardinal<T,U>
                                    )
  {
    return bitwise_cast<logical<T>>( is_not_greater_equal(a.bits(),b.bits()) );
  }
}

#endif
