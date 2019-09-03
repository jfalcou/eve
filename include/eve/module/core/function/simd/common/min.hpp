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
  // Regular
  template<typename T, typename U>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      std::conditional_t<is_vectorized_v<T>, T, U>,
      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    { return map(eve::min, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b)); }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::min, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_vectorized_v<T> & is_vectorized_v<U>)
    {
      if constexpr(std::is_same_v<T, U>) { return if_else(is_less(b, a), b, a); }
      else
      {
        static_assert(wrong<T, U>, "[eve::min] no support for current simd api");
        return {};
      }
    }
    else // if constexpr( is_vectorized_v<T> ^ is_vectorized_v<U> )
    {
      return eve::min(abi_cast<U>(a), abi_cast<T>(b));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_),
                            logical<T> const &a,
                            logical<U> const &b) noexcept requires(logical<T>,
                                                                   Vectorized<T>,
                                                                   Vectorized<U>,
                                                                   EqualCardinal<T, U>)
  {
    return logical_or(a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // Pedantic
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  min_(EVE_SUPPORTS(cpu_),
       pedantic_type const &,
       T const &v0,
       U const &v1) noexcept requires(std::conditional_t<is_vectorized_v<T>, T, U>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    if constexpr(std::is_integral_v<T> || is_logical_v<T>)
      return eve::min(v0, v1);
    else
      return if_else(is_nan(v1), v0, eve::min(v0, v1));
  }

  // -----------------------------------------------------------------------------------------------
  // Numeric
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  min_(EVE_SUPPORTS(cpu_),
       numeric_type const &,
       T const &v0,
       U const &v1) noexcept requires(std::conditional_t<is_vectorized_v<T>, T, U>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    if constexpr(std::is_integral_v<T> || is_logical_v<T>)
      return eve::min(v0, v1);
    else
      return if_else(is_nan(v0), v1, min(v0, v1));
  }
}

#endif
