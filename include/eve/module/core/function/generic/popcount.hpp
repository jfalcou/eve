//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_POPCOUNT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_POPCOUNT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <eve/traits.hpp>
#include <eve/detail/has_abi.hpp>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<integral_value T>
  EVE_FORCEINLINE as_integer_t<T, unsigned> popcount_(EVE_SUPPORTS(cpu_)
                                                     , T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
#if defined(SPY_COMPILER_IS_MSVC)
        std::uint8_t r = static_cast<std::uint8_t>(__popcnt16(static_cast<std::int16_t>(v) & 0xFF));
#else
        std::uint8_t  r   = __builtin_popcount(static_cast<std::uint32_t>(v) & 0xFF);
#endif
        return r;
      }

      if constexpr(sizeof(T) == 2)
      {
#if defined(SPY_COMPILER_IS_MSVC)
        std::uint16_t r = __popcnt16(v);
#else
        std::uint16_t r = __builtin_popcount(static_cast<std::uint32_t>(v) & 0xFFFF);
#endif
        return r;
      }

      if constexpr(sizeof(T) == 4)
      {
#if defined(SPY_COMPILER_IS_MSVC)
        std::uint32_t r = __popcnt(v);
#else
        std::uint32_t r = __builtin_popcount(v);
#endif
        return r;
      }

      if constexpr(sizeof(T) == 8)
      {
#if defined(SPY_COMPILER_IS_MSVC) && defined(_WIN64)
        std::uint64_t r = __popcnt64(v);
#else
        std::uint32_t hi0 = (static_cast<std::uint32_t>(v >> 32) & 0xFFFFFFFF);
        std::uint32_t lo0 = (v & 0xFFFFFFFF);

#  if defined(SPY_COMPILER_IS_MSVC)
        std::uint64_t r = __popcnt(hi0) + __popcnt(lo0);
#  else
        std::uint64_t r = __builtin_popcount(hi0) + __builtin_popcount(lo0);
#  endif

#endif
        return r;
      }
    }
    else if constexpr(has_native_abi_v<T>)
    {
      return map(eve::popcount, v);
    }
    else
    {
      return apply_over(popcount, v);
    }
  }
}

#endif
