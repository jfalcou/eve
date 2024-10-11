//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/traits/as_integer.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

namespace eve
{
  // ---------------------------------------------------------------------------------------------
  // NEON 64
  template<typename T, typename N>
  consteval auto find_register_type(as<T>, N, eve::arm_64_)
  {
    if constexpr (std::same_as<T, float> && (N::value <= 2))
    {
      return float32x2_t{};
    }
    else if constexpr (std::same_as<T, double> && (N::value <= 1))
    {
      #if defined(SPY_SIMD_IS_ARM_ASIMD)
      return float64x1_t{};
      #else
      return emulated_{};
      #endif
    }
    else if constexpr (std::signed_integral<T>)
    {
      if      constexpr((sizeof(T) == 1) && (N::value <= 8)) return int8x8_t{};
      else if constexpr((sizeof(T) == 2) && (N::value <= 4)) return int16x4_t{};
      else if constexpr((sizeof(T) == 4) && (N::value <= 2)) return int32x2_t{};
      else if constexpr((sizeof(T) == 8) && (N::value <= 1)) return int64x1_t{};
    }
    else if constexpr (std::unsigned_integral<T>)
    {
      if      constexpr((sizeof(T) == 1) && (N::value <= 8)) return uint8x8_t{};
      else if constexpr((sizeof(T) == 2) && (N::value <= 4)) return uint16x4_t{};
      else if constexpr((sizeof(T) == 4) && (N::value <= 2)) return uint32x2_t{};
      else if constexpr((sizeof(T) == 8) && (N::value <= 1)) return uint64x1_t{};
    }
  }

  // ---------------------------------------------------------------------------------------------
  // NEON 128
  template<typename T, typename N>
  consteval auto find_register_type(as<T>, N, eve::arm_128_)
  {
    if constexpr (std::same_as<T, float>)
    {
      return float32x4_t{};
    }
    else if constexpr (std::same_as<T, double>)
    {
      #if defined(SPY_SIMD_IS_ARM_ASIMD)
      return float64x2_t{};
      #else
      return emulated_{};
      #endif
    }
    else if constexpr (std::signed_integral<T>)
    {
      if      constexpr ((sizeof(T) == 1) && (N::value == 16)) return int8x16_t{};
      else if constexpr ((sizeof(T) == 2) && (N::value == 8 )) return int16x8_t{};
      else if constexpr ((sizeof(T) == 4) && (N::value == 4 )) return int32x4_t{};
      else if constexpr ((sizeof(T) == 8) && (N::value == 2 )) return int64x2_t{};
    }
    else if constexpr (std::unsigned_integral<T>)
    {
      if      constexpr ((sizeof(T) == 1) && (N::value == 16)) return uint8x16_t{};
      else if constexpr ((sizeof(T) == 2) && (N::value == 8 )) return uint16x8_t{};
      else if constexpr ((sizeof(T) == 4) && (N::value == 4 )) return uint32x4_t{};
      else if constexpr ((sizeof(T) == 8) && (N::value == 2 )) return uint64x2_t{};
    }
  }

  // ---------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename N>
  consteval auto find_logical_register_type(as<T>, N n, arm_abi auto abi)
  {
    return find_register_type(as_integer_t<T, unsigned>{}, n, abi);
  }
}
