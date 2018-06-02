//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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

namespace eve { namespace detail
{
  template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  EVE_FORCEINLINE auto popcnt_( EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( sizeof(T) == 1 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint8_t that = __popcnt16(static_cast<std::int16_t>(a0) & 0xFF);
      #else
      std::uint8_t that = __builtin_popcount(static_cast<std::uint32_t>(a0) & 0xFF);
      #endif

      return that;
    }

    if constexpr( sizeof(T) == 2 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint16_t that = __popcnt16(a0);
      #else
      std::uint16_t that = __builtin_popcount(static_cast<std::uint32_t>(a0) & 0xFFFF);
      #endif

      return that;
    }

    if constexpr( sizeof(T) == 4 )
    {
      #if defined(EVE_COMP_IS_MSVC)
      std::uint32_t that = __popcnt(a0);
      #else
      std::uint32_t that = __builtin_popcount(a0);
      #endif

      return that;
    }

    if constexpr( sizeof(T) == 8 )
    {
      #if defined(EVE_COMP_IS_MSVC) && defined(_WIN64)
      std::uint64_t that = __popcnt64(a0);
      #else
      std::uint32_t hi0 = (static_cast<std::uint32_t>(a0 >> 32) & 0xFFFFFFFF);
      std::uint32_t lo0 = (a0 & 0xFFFFFFFF);

      #if defined(EVE_COMP_IS_MSVC)
      std::uint64_t that = __popcnt(hi0) + __popcnt(lo0);
      #else
      std::uint64_t that = __builtin_popcount(hi0) + __builtin_popcount(lo0);
      #endif

      #endif

      return that;
    }
  }

  // Disallow popcnt on scalar floating-point types
  EVE_FORCEINLINE std::uint64_t popcnt_( EVE_SUPPORTS(cpu_), float      ) noexcept = delete;
  EVE_FORCEINLINE std::uint64_t popcnt_( EVE_SUPPORTS(cpu_), double     ) noexcept = delete;
} }

#endif
