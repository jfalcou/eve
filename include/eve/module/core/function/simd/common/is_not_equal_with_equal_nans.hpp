//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  is_not_equal_with_equal_nans_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      as_logical_t<std::conditional_t<is_vectorized_v<T>, T, U>>,
      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::is_not_equal_with_equal_nans,
                 abi_cast<value_type_t<U>>(a),
                 abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::is_not_equal_with_equal_nans,
                       abi_cast<value_type_t<U>>(a),
                       abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_vectorized_v<T> & is_vectorized_v<U>)
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(std::is_floating_point_v<value_type_t<T>>)
        { return is_not_equal(a, b) && (is_not_nan(a) || is_not_nan(b)); }
        else
        {
          return is_not_equal(a, b);
        }
      }
      else
      {
        static_assert(std::is_same_v<T, U>,
                      "[eve::is_not_equal_with_equal_nans]  - no support for current simd api");
        return {};
      }
    }
    else // if constexpr( is_vectorized_v<T> ^ is_vectorized_v<U> )
    {
      return eve::is_not_equal_with_equal_nans(abi_cast<U>(a), abi_cast<T>(b));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  is_not_equal_with_equal_nans_(EVE_SUPPORTS(cpu_),
                                logical<T> const &a,
                                logical<U> const &b) noexcept requires(logical<T>,
                                                                       Vectorized<T>,
                                                                       Vectorized<U>,
                                                                       EqualCardinal<T, U>)
  {
    return is_not_equal(a, b);
  }
}

#endif
