//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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

#if defined(EVE_HW_ARM)
namespace eve
{
  // ---------------------------------------------------------------------------------------------
  // NEON 64
  template<typename T, typename Size> struct as_register<T, Size, eve::arm_64_>
  {
    static constexpr auto find()
    {
      if constexpr( std::is_same_v<T,float> && Size::value <= 2)
      {
        return float32x2_t{};
      }
      else if constexpr( std::is_same_v<T,double> && Size::value <= 1 )
      {
        #if defined(SPY_SIMD_IS_ARM_ASIMD)
        return float64x1_t{};
        #else
        return emulated_{};
        #endif
      }
      else if constexpr( std::is_integral_v<T> )
      {
        constexpr bool signed_v = std::is_signed_v<T>;

        if constexpr(  signed_v && (sizeof(T) == 1 )&& (Size::value <= 8) ) return int8x8_t{};
        if constexpr(  signed_v && (sizeof(T) == 2 )&& (Size::value <= 4) ) return int16x4_t{};
        if constexpr(  signed_v && (sizeof(T) == 4 )&& (Size::value <= 2) ) return int32x2_t{};
        if constexpr(  signed_v && (sizeof(T) == 8 )&& (Size::value <= 1) ) return int64x1_t{};
        if constexpr( !signed_v && (sizeof(T) == 1 )&& (Size::value <= 8) ) return uint8x8_t{};
        if constexpr( !signed_v && (sizeof(T) == 2 )&& (Size::value <= 4) ) return uint16x4_t{};
        if constexpr( !signed_v && (sizeof(T) == 4 )&& (Size::value <= 2) ) return uint32x2_t{};
        if constexpr( !signed_v && (sizeof(T) == 8 )&& (Size::value <= 1) ) return uint64x1_t{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve arm] - Type is not usable in a SIMD register");
  };

  // ---------------------------------------------------------------------------------------------
  // NEON 128
  template<typename T, typename Size>
  struct as_register<T, Size, eve::arm_128_>
  {
    static constexpr auto find()
    {
      if constexpr( std::is_same_v<T,float> )
      {
        return float32x4_t{};
      }
      else if constexpr( std::is_same_v<T,double> )
      {
        #if defined(SPY_SIMD_IS_ARM_ASIMD)
        return float64x2_t{};
        #else
        return emulated_{};
        #endif
      }
      else if constexpr( std::is_integral_v<T> )
      {
        constexpr bool signed_v = std::is_signed_v<T>;
        if constexpr(  signed_v && (sizeof(T) == 1 )&& (Size::value == 16) ) return int8x16_t{};
        if constexpr(  signed_v && (sizeof(T) == 2 )&& (Size::value == 8 ) ) return int16x8_t{};
        if constexpr(  signed_v && (sizeof(T) == 4 )&& (Size::value == 4 ) ) return int32x4_t{};
        if constexpr(  signed_v && (sizeof(T) == 8 )&& (Size::value == 2 ) ) return int64x2_t{};
        if constexpr( !signed_v && (sizeof(T) == 1 )&& (Size::value == 16) ) return uint8x16_t{};
        if constexpr( !signed_v && (sizeof(T) == 2 )&& (Size::value == 8 ) ) return uint16x8_t{};
        if constexpr( !signed_v && (sizeof(T) == 4 )&& (Size::value == 4 ) ) return uint32x4_t{};
        if constexpr( !signed_v && (sizeof(T) == 8 )&& (Size::value == 2 ) ) return uint64x2_t{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve arm] - Type is not usable in a SIMD register");
  };

  // ---------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename Size, arm_abi ABI>
  struct  as_logical_register<T, Size, ABI>
        : as_register<as_integer_t<T, unsigned>, Size, ABI>
  {};
}
#endif
