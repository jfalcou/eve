//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  is_greater_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept Requires(
      as_logical_t<std::conditional_t<is_Vectorized_v<T>, T, U>>,
      detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::is_greater_equal, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(
          eve::is_greater_equal, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_Vectorized_v<T> & is_Vectorized_v<U>)
    {
      static_assert(wrong<T, U>, "[eve::is_greater_equal] - no support for current simd api ");
      return {};
    }
    else // if constexpr( is_Vectorized_v<T> ^ is_Vectorized_v<U> )
    {
      return eve::is_greater_equal(abi_cast<U>(a), abi_cast<T>(b));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  is_greater_equal_(EVE_SUPPORTS(cpu_),
                    logical<T> const &a,
                    logical<U> const &b) noexcept Requires(logical<T>,
                                                           Vectorized<T>,
                                                           Vectorized<U>,
                                                           equal_cardinal<T, U>)
  {
    return bit_cast(is_greater_equal(a.bits(), b.bits()),as(a));
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator>=(T const &v0, U const &v1) noexcept
      -> decltype(eve::is_greater_equal(v0, v1))
  {
    return eve::is_greater_equal(v0, v1);
  }
}

#endif
