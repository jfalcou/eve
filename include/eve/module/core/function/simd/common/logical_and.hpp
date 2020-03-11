//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/as_logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      as_logical_t<std::conditional_t<is_vectorized_v<T>, T, U>>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    if constexpr(!is_vectorized_v<U>) { return logical_and(a, T{b}); }
    else if constexpr(!is_vectorized_v<T>)
    {
      return logical_and(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<typename T::abi_type>)
        { return aggregate(eve::logical_and, a, b); }
        else if constexpr(is_emulated_v<typename T::abi_type>)
        {
          return map(eve::logical_and, a, b);
        }
        else
        {
          return bit_cast(bit_and(bit_mask(a), bit_mask(b)), as_<as_logical_t<T>>());
        }
      }
      else
      {
        static_assert(std::is_same_v<T, U>, "[eve::logical_and] - Incompatible types.");
        return {};
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_),
                                    logical<T> const &a,
                                    logical<U> const &b) noexcept requires(logical<T>,
                                                                           vectorized<T>,
                                                                           vectorized<U>,
                                                                           equal_cardinal<T, U>)
  {
    return bit_cast(bit_and(a.bits(), b.bits()), as(a));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_),
                                    logical<T> const &a,
                                    U const &         b) noexcept requires(logical<T>,
                                                                  vectorized<T>,
                                                                  vectorized<U>,
                                                                  equal_cardinal<T, U>)
  {
    return bit_cast(bit_and(a.bits(), bit_mask(b)), as(a));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_),
                                    T const &         a,
                                    logical<U> const &b) noexcept requires(logical<U>,
                                                                           vectorized<T>,
                                                                           vectorized<U>,
                                                                           equal_cardinal<T, U>)
  {
    return bit_cast(bit_and(bit_mask(a), b.bits()), as(b));
  }
}

#endif
