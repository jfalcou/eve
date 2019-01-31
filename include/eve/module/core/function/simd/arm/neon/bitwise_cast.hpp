//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/function/simd/detail/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, neon64_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<Source, N, neon64_> const &v0,
                                as_<wide<Target, M, neon64_>> const &) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<Source, Target>) return v0;

    using in_t  = typename wide<Source, N, neon64_>::storage_type;
    using tgt_t = typename wide<Target, M, neon64_>::storage_type;

// Dispatch to sub-functions
#if defined(__aarch64__)
    if constexpr(std::is_same_v<tgt_t, float64x1_t>)
    {
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_f64_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_f64_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_f64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_f64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_f64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_f64_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_f64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_f64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_f64_u8(v0);
    }
#endif

    if constexpr(std::is_same_v<tgt_t, float32x2_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_f32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_f32_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_f32_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_f32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_f32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_f32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_f32_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_f32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_f32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int64x1_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_s64_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_s64_f32(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_s64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_s64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_s64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_s64_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_s64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_s64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_s64_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint64x1_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_u64_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_u64_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_u64_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_u64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_u64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_u64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_u64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_u64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_u64_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int32x2_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_s32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_s32_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_s32_s64(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_s32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_s32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_s32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_s32_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_s32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_s32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint32x2_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_u32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_u32_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_u32_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_u32_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_u32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_u32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_u32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_u32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_u32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int16x4_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_s16_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_s16_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_s16_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_s16_s32(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_s16_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_s16_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_s16_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_s16_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_s16_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint16x4_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_u16_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_u16_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_u16_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_u16_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_u16_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_u16_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_u16_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_u16_u32(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_u16_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int8x8_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_s8_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_s8_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_s8_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_s8_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_s8_s16(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_s8_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_s8_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_s8_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x8_t>) return vreinterpret_s8_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint8x8_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x1_t>) return vreinterpret_u8_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x2_t>) return vreinterpret_u8_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x1_t>) return vreinterpret_u8_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x2_t>) return vreinterpret_u8_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x4_t>) return vreinterpret_u8_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x8_t>) return vreinterpret_u8_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x1_t>) return vreinterpret_u8_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x2_t>) return vreinterpret_u8_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x4_t>) return vreinterpret_u8_u16(v0);
    }
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, neon128_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<Source, N, neon128_> const &v0,
                                as_<wide<Target, M, neon128_>> const &) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<Source, Target>) return v0;

    using in_t  = typename wide<Source, N, neon128_>::storage_type;
    using tgt_t = typename wide<Target, M, neon128_>::storage_type;

// Dispatch to sub-functions
#if defined(__aarch64__)
    if constexpr(std::is_same_v<tgt_t, float64x2_t>)
    {
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_f64_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_f64_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_f64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_f64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_f64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_f64_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_f64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_f64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_f64_u8(v0);
    }
#endif

    if constexpr(std::is_same_v<tgt_t, float32x4_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_f32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_f32_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_f32_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_f32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_f32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_f32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_f32_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_f32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_f32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int64x2_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_s64_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_s64_f32(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_s64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_s64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_s64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_s64_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_s64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_s64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_s64_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint64x2_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_u64_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_u64_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_u64_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_u64_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_u64_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_u64_s8(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_u64_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_u64_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_u64_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int32x4_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_s32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_s32_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_s32_s64(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_s32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_s32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_s32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_s32_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_s32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_s32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint32x4_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_u32_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_u32_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_u32_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_u32_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_u32_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_u32_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_u32_u64(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_u32_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_u32_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int16x8_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_s16_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_s16_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_s16_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_s16_s32(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_s16_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_s16_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_s16_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_s16_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_s16_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint16x8_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_u16_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_u16_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_u16_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_u16_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_u16_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_u16_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_u16_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_u16_u32(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_u16_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, int8x16_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_s8_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_s8_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_s8_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_s8_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_s8_s16(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_s8_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_s8_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_s8_u16(v0);
      if constexpr(std::is_same_v<in_t, uint8x16_t>) return vreinterpretq_s8_u8(v0);
    }

    if constexpr(std::is_same_v<tgt_t, uint8x16_t>)
    {
#if defined(__aarch64__)
      if constexpr(std::is_same_v<in_t, float64x2_t>) return vreinterpretq_u8_f64(v0);
#endif
      if constexpr(std::is_same_v<in_t, float32x4_t>) return vreinterpretq_u8_f32(v0);
      if constexpr(std::is_same_v<in_t, int64x2_t>) return vreinterpretq_u8_s64(v0);
      if constexpr(std::is_same_v<in_t, int32x4_t>) return vreinterpretq_u8_s32(v0);
      if constexpr(std::is_same_v<in_t, int16x8_t>) return vreinterpretq_u8_s16(v0);
      if constexpr(std::is_same_v<in_t, int8x16_t>) return vreinterpretq_u8_s8(v0);
      if constexpr(std::is_same_v<in_t, uint64x2_t>) return vreinterpretq_u8_u64(v0);
      if constexpr(std::is_same_v<in_t, uint32x4_t>) return vreinterpretq_u8_u32(v0);
      if constexpr(std::is_same_v<in_t, uint16x8_t>) return vreinterpretq_u8_u16(v0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // NEON supports logical bitwise casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<logical<Target>, M, neon128_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<Source, N, neon128_> const &              v0,
                                as_<wide<logical<Target>, M, neon128_>> const &tgt) noexcept
  {
    return a2l_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<logical<Target>, M, neon64_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<Source, N, neon64_> const &              v0,
                                as_<wide<logical<Target>, M, neon64_>> const &tgt) noexcept
  {
    return a2l_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, neon128_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<logical<Source>, N, neon128_> const &v0,
                                as_<wide<Target, M, neon128_>> const &    tgt) noexcept
  {
    return l2a_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, neon64_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<logical<Source>, N, neon64_> const &v0,
                                as_<wide<Target, M, neon64_>> const &    tgt) noexcept
  {
    return l2a_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<logical<Target>, M, neon128_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<logical<Source>, N, neon128_> const &     v0,
                                as_<wide<logical<Target>, M, neon128_>> const &tgt) noexcept
  {
    return l2l_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<logical<Target>, M, neon64_>
                  bitwise_cast_(EVE_SUPPORTS(neon128_),
                                wide<logical<Source>, N, neon64_> const &     v0,
                                as_<wide<logical<Target>, M, neon64_>> const &tgt) noexcept
  {
    return l2l_cast_(v0, tgt);
  }
}

#endif
