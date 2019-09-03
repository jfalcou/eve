//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      as_logical_t<std::conditional_t<is_vectorized_v<T>, T, U>>,
      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    if constexpr(!is_vectorized_v<U>) { return logical_xor(a, T{b}); }
    else if constexpr(!is_vectorized_v<T>)
    {
      return logical_xor(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<typename T::abi_type>)
        { return aggregate(eve::logical_xor, a, b); }
        else if constexpr(is_emulated_v<typename T::abi_type>)
        {
          return map(eve::logical_xor, a, b);
        }
        else
        {
          return bitwise_cast<as_logical_t<T>>(bitwise_xor(bitwise_mask(a), bitwise_mask(b)));
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
                                    logical<U> const &b) noexcept requires(logical<T>,
                                                                           Vectorized<T>,
                                                                           Vectorized<U>,
                                                                           EqualCardinal<T, U>)
  {
    return bitwise_cast<logical<T>>(bitwise_xor(a.bits(), b.bits()));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_),
                                    logical<T> const &a,
                                    U const &         b) noexcept requires(logical<T>,
                                                                  Vectorized<T>,
                                                                  Vectorized<U>,
                                                                  EqualCardinal<T, U>)
  {
    return bitwise_cast<logical<T>>(bitwise_xor(a.bits(), bitwise_mask(b)));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_),
                                    T const &         a,
                                    logical<U> const &b) noexcept requires(logical<U>,
                                                                           Vectorized<T>,
                                                                           Vectorized<U>,
                                                                           EqualCardinal<T, U>)
  {
    return bitwise_cast<logical<U>>(bitwise_xor(bitwise_mask(a), b.bits()));
  }
}

#endif
