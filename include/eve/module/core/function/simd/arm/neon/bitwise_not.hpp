//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_BITWISE_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_BITWISE_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> bitwise_not_(EVE_SUPPORTS(neon128_),
                                                   wide<T, N, neon64_> const &v0) noexcept
  {
    using t_t  = wide<T, N, neon64_>;
    using i_t  = wide<as_integer_t<T, unsigned>, N>;
    using in_t = typename t_t::storage_type;

    if constexpr(std::is_floating_point_v<T>)
      return bitwise_cast<t_t>(bitwise_not(bitwise_cast<i_t>(v0)));

    if constexpr(std::is_same_v<in_t, int64x1_t>)
      return vreinterpret_s64_s32(vmvn_s32(vreinterpret_s32_s64(v0)));

    if constexpr(std::is_same_v<in_t, uint64x1_t>)
      return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(v0)));

    if constexpr(std::is_same_v<in_t, int32x2_t>) return vmvn_s32(v0);
    if constexpr(std::is_same_v<in_t, int16x4_t>) return vmvn_s16(v0);
    if constexpr(std::is_same_v<in_t, int8x8_t>) return vmvn_s8(v0);
    if constexpr(std::is_same_v<in_t, uint32x2_t>) return vmvn_u32(v0);
    if constexpr(std::is_same_v<in_t, uint16x4_t>) return vmvn_u16(v0);
    if constexpr(std::is_same_v<in_t, uint8x8_t>) return vmvn_u8(v0);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> bitwise_not_(EVE_SUPPORTS(neon128_),
                                                    wide<T, N, neon128_> const &v0) noexcept
  {
    using t_t  = wide<T, N, neon128_>;
    using i_t  = wide<as_integer_t<T, unsigned>, N>;
    using in_t = typename t_t::storage_type;

    if constexpr(std::is_floating_point_v<T>)
      return bitwise_cast<t_t>(bitwise_not(bitwise_cast<i_t>(v0)));

    if constexpr(std::is_same_v<in_t, int64x2_t>)
      return vreinterpretq_s64_s32(vmvnq_s32(vreinterpretq_s32_s64(v0)));

    if constexpr(std::is_same_v<in_t, uint64x2_t>)
      return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(v0)));

    if constexpr(std::is_same_v<in_t, int32x4_t>) return vmvnq_s32(v0);
    if constexpr(std::is_same_v<in_t, int16x8_t>) return vmvnq_s16(v0);
    if constexpr(std::is_same_v<in_t, int8x16_t>) return vmvnq_s8(v0);
    if constexpr(std::is_same_v<in_t, uint32x4_t>) return vmvnq_u32(v0);
    if constexpr(std::is_same_v<in_t, uint16x8_t>) return vmvnq_u16(v0);
    if constexpr(std::is_same_v<in_t, uint8x16_t>) return vmvnq_u8(v0);
  }
}

#endif
