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
    else if constexpr ( std::same_as<Struct, int8x8x2_t>    ) return wide<std::int8_t  , fixed<4>>{};
    else if constexpr ( std::same_as<Struct, uint8x8x2_t>   ) return wide<std::uint8_t , fixed<4>>{};
    // 16 byte
    else if constexpr ( std::same_as<Struct, int64x2x2_t>   ) return wide<std::int64_t , fixed<2>> {};
    else if constexpr ( std::same_as<Struct, uint64x2x2_t>  ) return wide<std::uint64_t, fixed<2>> {};
    else if constexpr ( std::same_as<Struct, float32x4x2_t> ) return wide<float        , fixed<4>> {};
    else if constexpr ( std::same_as<Struct, int32x4x2_t>   ) return wide<std::int32_t , fixed<4>> {};
    else if constexpr ( std::same_as<Struct, uint32x4x2_t>  ) return wide<std::uint32_t, fixed<4>> {};
    else if constexpr ( std::same_as<Struct, int16x8x2_t>   ) return wide<std::int16_t , fixed<8>>{};
    else if constexpr ( std::same_as<Struct, uint16x8x2_t>  ) return wide<std::uint16_t, fixed<8>>{};
    else if constexpr ( std::same_as<Struct, int8x16x2_t>   ) return wide<std::int8_t  , fixed<8>>{};
    else if constexpr ( std::same_as<Struct, uint8x16x2_t>  ) return wide<std::uint8_t , fixed<8>>{};
    // doubles
#if defined(SPY_SIMD_IS_ARM_ASIMD)
    else if constexpr ( std::same_as<Struct, float64x1x2_t> ) return wide<double       , fixed<1>>{};
    else if constexpr ( std::same_as<Struct, float64x2x2_t> ) return wide<double       , fixed<2>>{};
#endif
  }

  template <typename Struct>
  EVE_FORCEINLINE
  auto neon_struct_to_wide(Struct s)
  {
   using half = decltype(neon_struct_to_wide_type<Struct>());
   return eve::combine(half(s.val[0]), half(s.val[1]));
  }
}
