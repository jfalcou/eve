//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>

#include <cstddef>
#include <type_traits>

namespace eve::detail
{
  enum class category : std::uint32_t
  {
    // Building blocks
    int_      = 0x01000000,
    uint_     = 0x02000000,
    float_    = 0x04000000,
    unsigned_ = 0x02000000,
    integer_  = int_ | uint_,
    signed_   = int_ | float_,
    size64_   = 0x00080000,
    size32_   = 0x00040000,
    size16_   = 0x00020000,
    size8_    = 0x00010000,
    invalid   = 0x00000000,

    // All known native float64
    float64x1   = float_ | size64_ | 1,
    float64x2   = float_ | size64_ | 2,
    float64x4   = float_ | size64_ | 4,
    float64x8   = float_ | size64_ | 8,

    // All known native float32
    float32x2   = float_ | size32_ | 2  ,
    float32x4   = float_ | size32_ | 4  ,
    float32x8   = float_ | size32_ | 8  ,
    float32x16  = float_ | size32_ | 16 ,

    // All known native ?int8
     int8_    =  int_   | size8_,
    uint8_    = uint_   | size8_,
     int8x8   =  int8_  | 8     ,
     int8x16  =  int8_  | 16    ,
     int8x32  =  int8_  | 32    ,
     int8x64  =  int8_  | 64    ,
    uint8x8   = uint8_  | 8     ,
    uint8x16  = uint8_  | 16    ,
    uint8x32  = uint8_  | 32    ,
    uint8x64  = uint8_  | 64    ,

    // All known native ?int16
     int16_   =  int_   | size16_ ,
    uint16_   = uint_   | size16_ ,
     int16x4  =  int16_ | 4       ,
     int16x8  =  int16_ | 8       ,
     int16x16 =  int16_ | 16      ,
     int16x32 =  int16_ | 32      ,
    uint16x4  = uint16_ | 4       ,
    uint16x8  = uint16_ | 8       ,
    uint16x16 = uint16_ | 16      ,
    uint16x32 = uint16_ | 32      ,

    // All known native ?int32
     int32_   =  int_   | size32_ ,
    uint32_   = uint_   | size32_ ,
     int32x2  =  int32_ | 2       ,
     int32x4  =  int32_ | 4       ,
     int32x8  =  int32_ | 8       ,
     int32x16 =  int32_ | 16      ,
    uint32x2  = uint32_ | 2       ,
    uint32x4  = uint32_ | 4       ,
    uint32x8  = uint32_ | 8       ,
    uint32x16 = uint32_ | 16      ,

    // All known native ?int64
     int64_   =  int_   | size64_ ,
    uint64_   = uint_   | size64_ ,
     int64x1  =  int64_ | 1       ,
     int64x2  =  int64_ | 2       ,
     int64x4  =  int64_ | 4       ,
     int64x8  =  int64_ | 8       ,
    uint64x1  = uint64_ | 1       ,
    uint64x2  = uint64_ | 2       ,
    uint64x4  = uint64_ | 4       ,
    uint64x8  = uint64_ | 8
  };

  EVE_FORCEINLINE constexpr std::uint32_t to_int(category a) noexcept
  {
    return static_cast<std::uint32_t>(a);
  }

  EVE_FORCEINLINE constexpr category operator|(category a, category b) noexcept
  {
    return static_cast<category>(to_int(a) | to_int(b));
  }

  EVE_FORCEINLINE constexpr bool operator&&(category a, category b) noexcept
  {
    return (to_int(a) & to_int(b)) != 0;
  }

  template<typename W> EVE_FORCEINLINE constexpr category categorize() noexcept
  {
    if constexpr( has_native_abi_v<W> )
    {
      using type      = typename W::value_type;
      using storage_t = typename W::storage_type;
      category value{};

      // Base type
            if constexpr( std::is_floating_point_v<type>) value = value | category::float_;
      else  if constexpr( std::is_signed_v<type>        ) value = value | category::int_;
      else  if constexpr( std::is_unsigned_v<type>      ) value = value | category::uint_;

      // Base type size & Cardinal
      constexpr auto card = static_cast<category>(sizeof(storage_t) / sizeof(type));
      constexpr auto sz   = static_cast<category>(sizeof(type) << 16);

      return value | sz | card;
    }
    else
    {
      return category::invalid;
    }
  }
}
