//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NOT_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NOT_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/is_wide.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr as_logical_t<std::conditional_t<is_wide_v<T>,T,U>>
  is_not_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    if constexpr( is_wide_v<T> && is_wide_v<U> )
    {
      if constexpr(!std::is_same_v<T,U>)
      {
        static_assert( std::is_same_v<T,U>, "[eve::is_not_equal] - Incompatible types.");
        return {};
      }
      else
      {
        if constexpr( is_native_v<typename T::abi_type> )
        {
          if constexpr( is_logical_v<typename T::value_type> )
          {
            return a != b;
          }
          else
          {
            return logical_not(is_equal(a, b));
          }
        }
        else
        {
          if constexpr( is_aggregated_v<typename T::abi_type> )
          {
            return aggregate( eve::is_not_equal, a, b);
          }

          if constexpr( is_emulated_v<typename T::abi_type> )
          {
            return map( eve::is_not_equal, a, b);
          }
        }
      }
    }
    else if constexpr( is_wide_v<T> && !is_wide_v<U> )
    {
      return is_not_equal(a, T{b});
    }
    else if constexpr( !is_wide_v<T> && is_wide_v<U> )
    {
      return is_not_equal(U{a},b);
    }
    else
    {
      return a != b;
    }
  }
}

#endif
