//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept Requires(
      as_logical_t<std::conditional_t<is_Vectorized_v<T>, T, U>>,
      detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    if constexpr(!is_Vectorized_v<U>)
    {
      return logical_xor(a, T{b});
    }
    else if constexpr(!is_Vectorized_v<T>)
    {
      return logical_xor(U{a}, b);
    }
    else
    {
      if constexpr(sizeof(T) == sizeof(U)
                   && sizeof(value_type_t<T>)== sizeof(value_type_t<U>))
      {
        if constexpr(is_aggregated_v<typename T::abi_type>)
        {
          return aggregate(eve::logical_xor, a, b);
        }
        else if constexpr(is_emulated_v<typename T::abi_type>)
        {
          return map(eve::logical_xor, a, b);
        }
        else
        {
          return bit_cast(bit_xor(bit_mask(a), bit_mask(b)), as_<as_logical_t<T>>());
        }
      }
      else
      {
        static_assert(std::is_same_v<T, U>, "[eve::logical_xor] - Incompatible types.");
        return {};
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_),
                                    logical<T> const &a,
                                    logical<U> const &b) noexcept Requires(logical<T>,
                                                                           Vectorized<T>,
                                                                           Vectorized<U>,
                                                                           equal_cardinal<T, U>)
  {
    return bit_cast(bit_xor(a.bits(), b.bits()), as(a));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_),
                                    logical<T> const &a,
                                    U const &         b) noexcept Requires(logical<T>,
                                                                  Vectorized<T>,
                                                                  Vectorized<U>,
                                                                  equal_cardinal<T, U>)
  {
    return bit_cast(bit_xor(a.bits(), bit_mask(b)), as(a));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_),
                                    T const &         a,
                                    logical<U> const &b) noexcept Requires(logical<U>,
                                                                           Vectorized<T>,
                                                                           Vectorized<U>,
                                                                           equal_cardinal<T, U>)
  {
    return bit_cast(bit_xor(bit_mask(a), b.bits()), as(b));
  }
}

#endif
