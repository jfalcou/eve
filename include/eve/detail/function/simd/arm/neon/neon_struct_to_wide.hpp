//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/combine.hpp>

namespace eve::detail
{

  template <typename Struct>
  auto neon_struct_to_wide_type()
  {
         if constexpr ( std::same_as<Struct, int64x1x2_t>   ) return wide<std::int64_t , fixed<1>>{};
    else if constexpr ( std::same_as<Struct, uint64x1x2_t>  ) return wide<std::uint64_t, fixed<1>>{};
    else if constexpr ( std::same_as<Struct, float32x2x2_t> ) return wide<float        , fixed<2>>{};
    else if constexpr ( std::same_as<Struct, int32x2x2_t>   ) return wide<std::int32_t , fixed<2>>{};
    else if constexpr ( std::same_as<Struct, uint32x2x2_t>  ) return wide<std::uint32_t, fixed<2>>{};
    else if constexpr ( std::same_as<Struct, int16x4x2_t>   ) return wide<std::int16_t , fixed<4>>{};
    else if constexpr ( std::same_as<Struct, uint16x4x2_t>  ) return wide<std::uint16_t, fixed<4>>{};
    else if constexpr ( std::same_as<Struct, int8x8x2_t>    ) return wide<std::int8_t  , fixed<8>>{};
    else if constexpr ( std::same_as<Struct, uint8x8x2_t>   ) return wide<std::uint8_t , fixed<8>>{};
    // 16 byte
    else if constexpr ( std::same_as<Struct, int64x2x2_t>   ) return wide<std::int64_t , fixed<2>> {};
    else if constexpr ( std::same_as<Struct, uint64x2x2_t>  ) return wide<std::uint64_t, fixed<2>> {};
    else if constexpr ( std::same_as<Struct, float32x4x2_t> ) return wide<float        , fixed<4>> {};
    else if constexpr ( std::same_as<Struct, int32x4x2_t>   ) return wide<std::int32_t , fixed<4>> {};
    else if constexpr ( std::same_as<Struct, uint32x4x2_t>  ) return wide<std::uint32_t, fixed<4>> {};
    else if constexpr ( std::same_as<Struct, int16x8x2_t>   ) return wide<std::int16_t , fixed<8>>{};
    else if constexpr ( std::same_as<Struct, uint16x8x2_t>  ) return wide<std::uint16_t, fixed<8>>{};
    else if constexpr ( std::same_as<Struct, int8x16x2_t>   ) return wide<std::int8_t  , fixed<16>>{};
    else if constexpr ( std::same_as<Struct, uint8x16x2_t>  ) return wide<std::uint8_t , fixed<16>>{};
    // doubles
#if defined(SPY_SIMD_IS_ARM_ASIMD)
    else if constexpr ( std::same_as<Struct, float64x1x2_t> ) return wide<double       , fixed<1>>{};
    else if constexpr ( std::same_as<Struct, float64x2x2_t> ) return wide<double       , fixed<2>>{};
#endif
  }

  template <typename T, typename N>
  auto neon_wide_to_struct_of_2_type()
  {
    // <= 8 bytes
         if constexpr ( std::same_as<T, std::int64_t>  && N() == 1 ) return int64x1x2_t{};
    else if constexpr ( std::same_as<T, std::uint64_t> && N() == 1 ) return uint64x1x2_t{};
    else if constexpr ( std::same_as<T, float>         && N() <= 2 ) return float32x2x2_t{};
    else if constexpr ( std::same_as<T, std::int32_t>  && N() <= 2 ) return int32x2x2_t{};
    else if constexpr ( std::same_as<T, std::uint32_t> && N() <= 2 ) return uint32x2x2_t{};
    else if constexpr ( std::same_as<T, std::int16_t>  && N() <= 4 ) return int16x4x2_t{};
    else if constexpr ( std::same_as<T, std::uint16_t> && N() <= 4 ) return uint16x4x2_t{};
    else if constexpr ( std::same_as<T, std::int8_t>   && N() <= 8 ) return int8x8x2_t{};
    else if constexpr ( std::same_as<T, std::uint8_t>  && N() <= 8 ) return uint8x8x2_t{};
    // 16 bytes
    else if constexpr ( std::same_as<T, std::int64_t>  ) return int64x2x2_t{};
    else if constexpr ( std::same_as<T, std::uint64_t> ) return uint64x2x2_t{};
    else if constexpr ( std::same_as<T, float>         ) return float32x4x2_t{};
    else if constexpr ( std::same_as<T, std::int32_t>  ) return int32x4x2_t{};
    else if constexpr ( std::same_as<T, std::uint32_t> ) return uint32x4x2_t{};
    else if constexpr ( std::same_as<T, std::int16_t>  ) return int16x8x2_t{};
    else if constexpr ( std::same_as<T, std::uint16_t> ) return uint16x8x2_t{};
    else if constexpr ( std::same_as<T, std::int8_t>   ) return int8x16x2_t{};
    else if constexpr ( std::same_as<T, std::uint8_t>  ) return uint8x16x2_t{};
    // doubles
#if defined(SPY_SIMD_IS_ARM_ASIMD)
    else if constexpr ( std::same_as<T, double> && N() == 1 ) return float64x1x2_t{};
    else if constexpr ( std::same_as<T, double>             ) return float64x2x2_t{};
#endif
  }

  template <typename Struct>
  EVE_FORCEINLINE
  auto neon_struct_to_wide(Struct s)
  {
   using half = decltype(neon_struct_to_wide_type<Struct>());
   return eve::combine(half(s.val[0]), half(s.val[1]));
  }

  template <typename T, typename N>
  auto wide_to_neon_struct(wide<T, N> a, wide<T, N> b)
  {
    using r_t = decltype(neon_wide_to_struct_of_2_type<T, N>());
    return r_t{a, b};
  }
}
