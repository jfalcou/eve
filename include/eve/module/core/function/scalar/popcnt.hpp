//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>

#if defined(EVE_COMP_IS_MSVC)
#include <intrin.h>
#endif

namespace eve::detail
{
  template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  EVE_FORCEINLINE constexpr auto popcnt_( EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( sizeof(T) == 1 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint8_t r = static_cast<std::uint8_t>(__popcnt16(static_cast<std::int16_t>(a0) & 0xFF));
      #else
      std::uint8_t r = __builtin_popcount(static_cast<std::uint32_t>(a0) & 0xFF);
      #endif

      return r;
    }

    if constexpr( sizeof(T) == 2 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint16_t r = __popcnt16(a0);
      #else
      std::uint16_t r = __builtin_popcount(static_cast<std::uint32_t>(a0) & 0xFFFF);
      #endif

      return r;
    }

    if constexpr( sizeof(T) == 4 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint32_t r = __popcnt(a0);
      #else
      std::uint32_t r = __builtin_popcount(a0);
      #endif

      return r;
    }

    if constexpr( sizeof(T) == 8 )
    {
      #if defined(EVE_COMP_IS_MSVC) && defined(_WIN64)
      std::uint64_t r = __popcnt64(a0);
      #else
      std::uint32_t hi0 = (static_cast<std::uint32_t>(a0 >> 32) & 0xFFFFFFFF);
      std::uint32_t lo0 = (a0 & 0xFFFFFFFF);

      #if defined(EVE_COMP_IS_MSVC)
      std::uint64_t r = __popcnt(hi0) + __popcnt(lo0);
      #else
      std::uint64_t r = __builtin_popcount(hi0) + __builtin_popcount(lo0);
      #endif

      #endif

      return r;
    }
  }

  // Disallow popcnt on scalar floating-point types
  EVE_FORCEINLINE std::uint64_t popcnt_( EVE_SUPPORTS(cpu_), float      ) noexcept = delete;
  EVE_FORCEINLINE std::uint64_t popcnt_( EVE_SUPPORTS(cpu_), double     ) noexcept = delete;
}

#endif
