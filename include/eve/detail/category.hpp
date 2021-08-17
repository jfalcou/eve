//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
     int8    =  int_   | size8_,
    uint8    = uint_   | size8_,
     int8x8   =  int8  | 8     ,
     int8x16  =  int8  | 16    ,
     int8x32  =  int8  | 32    ,
     int8x64  =  int8  | 64    ,
    uint8x8   = uint8  | 8     ,
    uint8x16  = uint8  | 16    ,
    uint8x32  = uint8  | 32    ,
    uint8x64  = uint8  | 64    ,

    // All known native ?int16
     int16   =  int_   | size16_ ,
    uint16   = uint_   | size16_ ,
     int16x4  =  int16 | 4       ,
     int16x8  =  int16 | 8       ,
     int16x16 =  int16 | 16      ,
     int16x32 =  int16 | 32      ,
    uint16x4  = uint16 | 4       ,
    uint16x8  = uint16 | 8       ,
    uint16x16 = uint16 | 16      ,
    uint16x32 = uint16 | 32      ,

    // All known native ?int32
     int32   =  int_   | size32_ ,
    uint32   = uint_   | size32_ ,
     int32x2  =  int32 | 2       ,
     int32x4  =  int32 | 4       ,
     int32x8  =  int32 | 8       ,
     int32x16 =  int32 | 16      ,
    uint32x2  = uint32 | 2       ,
    uint32x4  = uint32 | 4       ,
    uint32x8  = uint32 | 8       ,
    uint32x16 = uint32 | 16      ,

    // All known native ?int64
     int64   =  int_   | size64_ ,
    uint64   = uint_   | size64_ ,
     int64x1  =  int64 | 1       ,
     int64x2  =  int64 | 2       ,
     int64x4  =  int64 | 4       ,
     int64x8  =  int64 | 8       ,
    uint64x1  = uint64 | 1       ,
    uint64x2  = uint64 | 2       ,
    uint64x4  = uint64 | 4       ,
    uint64x8  = uint64 | 8
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

  template<typename... Cat>
  EVE_FORCEINLINE constexpr bool match(category a, Cat... tst) noexcept
  {
    return ((a == tst) || ...);
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
