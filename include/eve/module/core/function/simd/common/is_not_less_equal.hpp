//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_LESS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_LESS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  is_not_less_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      as_logical_t<std::conditional_t<is_vectorized_v<T>, T, U>>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(
          eve::is_not_less_equal, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(
          eve::is_not_less_equal, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_vectorized_v<T> & is_vectorized_v<U>)
    {
      if constexpr(std::is_floating_point_v<value_type_t<T>>)
      { return is_greater(a, b) || is_unordered(a, b); }
      else
      {
        return is_greater(a, b);
      }
    }
    else // if constexpr( is_vectorized_v<T> ^ is_vectorized_v<U> )
    {
      return eve::is_not_less_equal(abi_cast<U>(a), abi_cast<T>(b));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto
  is_not_less_equal_(EVE_SUPPORTS(cpu_),
                     logical<T> const &a,
                     logical<U> const &b) noexcept requires(logical<T>,
                                                            vectorized<T>,
                                                            vectorized<U>,
                                                            equal_cardinal<T, U>)
  {
    return is_greater(a, b);
  }
}

#endif
