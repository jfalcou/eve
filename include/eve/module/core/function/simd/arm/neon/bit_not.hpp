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

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI_> bit_not_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, ABI> const &v0) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();
    using i_t  = wide<as_integer_t<T, unsigned>, N>;

         if constexpr(std::is_floating_point_v<T>)
            return bit_cast(bit_not(bit_cast(v0,as_<i_t>{})), as(v0));
    else if constexpr(cat == category::int64x1)
            return vreinterpret_s64_s32(vmvn_s32(vreinterpret_s32_s64(v0)));
    else if constexpr(cat == category::uint64x1)
            return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(v0)));
    else if constexpr(cat == category::int32x2)  return vmvn_s32(v0);
    else if constexpr(cat == category::int16x4)  return vmvn_s16(v0);
    else if constexpr(cat == category::int8x8)   return vmvn_s8(v0);
    else if constexpr(cat == category::uint32x2) return vmvn_u32(v0);
    else if constexpr(cat == category::uint16x4) return vmvn_u16(v0);
    else if constexpr(cat == category::uint8x8)  return vmvn_u8(v0);
    else if constexpr(cat == category::int64x2)
            return vreinterpretq_s64_s32(vmvnq_s32(vreinterpretq_s32_s64(v0)));
    else if constexpr(cat == category::uint64x2)
            return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(v0)));
    else if constexpr(cat == category::int32x4)  return vmvnq_s32(v0);
    else if constexpr(cat == category::int16x8)  return vmvnq_s16(v0);
    else if constexpr(cat == category::int8x16)  return vmvnq_s8(v0);
    else if constexpr(cat == category::uint32x4) return vmvnq_u32(v0);
    else if constexpr(cat == category::uint16x8) return vmvnq_u16(v0);
    else if constexpr(cat == category::uint8x16) return vmvnq_u8(v0);
  }
}

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> bit_not_(EVE_SUPPORTS(neon128_),
//                                                    wide<T, N, arm_64_> const &v0) noexcept
//   {
//     using i_t  = wide<as_integer_t<T, unsigned>, N>;
//     using in_t = typename wide<T, N, arm_64_>::storage_type;

//          if constexpr(std::is_floating_point_v<T>)
//             return bit_cast(bit_not(bit_cast(v0,as_<i_t>{})), as(v0));
//     else if constexpr(std::is_same_v<in_t, int64x1_t>)
//             return vreinterpret_s64_s32(vmvn_s32(vreinterpret_s32_s64(v0)));
//     else if constexpr(std::is_same_v<in_t, uint64x1_t>)
//             return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(v0)));
//     else if constexpr(std::is_same_v<in_t, int32x2_t>) return vmvn_s32(v0);
//     else if constexpr(std::is_same_v<in_t, int16x4_t>) return vmvn_s16(v0);
//     else if constexpr(std::is_same_v<in_t, int8x8_t>) return vmvn_s8(v0);
//     else if constexpr(std::is_same_v<in_t, uint32x2_t>) return vmvn_u32(v0);
//     else if constexpr(std::is_same_v<in_t, uint16x4_t>) return vmvn_u16(v0);
//     else if constexpr(std::is_same_v<in_t, uint8x8_t>) return vmvn_u8(v0);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> bit_not_(EVE_SUPPORTS(neon128_),
//                                                     wide<T, N, arm_128_> const &v0) noexcept
//   {
//     using i_t  = wide<as_integer_t<T, unsigned>, N>;
//     using in_t = typename wide<T, N, arm_128_>::storage_type;

//          if constexpr(std::is_floating_point_v<T>)
//             return bit_cast(bit_not(bit_cast(v0,as_<i_t>{})),as(v0));
//     else if constexpr(std::is_same_v<in_t, int64x2_t>)
//             return vreinterpretq_s64_s32(vmvnq_s32(vreinterpretq_s32_s64(v0)));
//     else if constexpr(std::is_same_v<in_t, uint64x2_t>)
//             return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(v0)));
//     else if constexpr(std::is_same_v<in_t, int32x4_t>) return vmvnq_s32(v0);
//     else if constexpr(std::is_same_v<in_t, int16x8_t>) return vmvnq_s16(v0);
//     else if constexpr(std::is_same_v<in_t, int8x16_t>) return vmvnq_s8(v0);
//     else if constexpr(std::is_same_v<in_t, uint32x4_t>) return vmvnq_u32(v0);
//     else if constexpr(std::is_same_v<in_t, uint16x8_t>) return vmvnq_u16(v0);
//     else if constexpr(std::is_same_v<in_t, uint8x16_t>) return vmvnq_u8(v0);
//   }
// }
