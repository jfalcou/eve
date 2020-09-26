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

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>
                  convert_(EVE_SUPPORTS(neon128_), wide<T, N, arm_64_> const &v0, as_<U> const &tgt) noexcept
  {
    using in_t  = typename wide<T, N, arm_64_>::storage_type;
    using tgt_t = typename wide<U, N>::storage_type;

    // Idempotent call
    if constexpr( std::is_same_v<T, U> )
      return v0;

#if defined(__aarch64__)
    //==============================================================================================
    // double -> ?
    if constexpr( std::is_same_v<in_t, float64x1_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int64x1_t> )
        return vcvt_s64_f64(v0);
      else if constexpr( std::is_same_v<tgt_t, uint64x1_t> )
        return vcvt_u64_f64(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
#endif
    //==============================================================================================
    // float -> ?
    if constexpr( std::is_same_v<in_t, float32x2_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int32x2_t> )
        return vcvt_s32_f32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint32x2_t> )
        return vcvt_u32_f32(v0);
      else if constexpr( std::is_same_v<tgt_t, int64x2_t> )
        return vmovl_s32(vcvt_s32_f32(v0));
      else if constexpr( std::is_same_v<tgt_t, uint64x2_t> )
        return vmovl_u32(vcvt_u32_f32(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int64 -> ?
    else if constexpr( std::is_same_v<in_t, int64x1_t> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<tgt_t, float64x1_t> )
        return vcvt_f64_s64(v0);
#endif
      if constexpr( std::is_same_v<tgt_t, uint64x1_t> )
        return vreinterpret_u64_s64(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint64 -> ?
    else if constexpr( std::is_same_v<in_t, uint64x1_t> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<tgt_t, float64x1_t> )
        return vcvt_f64_u64(v0);
#endif
      if constexpr( std::is_same_v<tgt_t, int64x1_t> )
        return vreinterpret_s64_u64(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int32 -> ?
    else if constexpr( std::is_same_v<in_t, int32x2_t> )
    {
      if constexpr( std::is_same_v<tgt_t, float32x2_t> )
        return vcvt_f32_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint32x2_t> )
        return vreinterpret_u32_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, int64x2_t> )
        return vmovl_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint64x2_t> )
        return vreinterpretq_u64_s64(vmovl_s32(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint32 -> ?
    else if constexpr( std::is_same_v<in_t, uint32x2_t> )
    {
      if constexpr( std::is_same_v<tgt_t, float32x2_t> )
        return vcvt_f32_u32(v0);
      else if constexpr( std::is_same_v<tgt_t, int32x2_t> )
        return vreinterpret_s32_u32(v0);
      else if constexpr( std::is_same_v<tgt_t, int64x2_t> )
        return vreinterpretq_s64_u64(vmovl_u32(v0));
      else if constexpr( std::is_same_v<tgt_t, uint64x2_t> )
        return vmovl_u32(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int16 -> ?
    else if constexpr( std::is_same_v<in_t, int16x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vmovl_s16(v0);
      else if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_s32(vmovl_s16(v0));
      else if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vreinterpretq_u32_s32(vmovl_s16(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x4_t> )
        return vreinterpret_u16_s16(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint16 -> ?
    else if constexpr( std::is_same_v<in_t, uint16x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vreinterpretq_s32_u32(vmovl_u16(v0));
      else if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_u32(vmovl_u16(v0));
      else if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vmovl_u16(v0);
      else if constexpr( std::is_same_v<tgt_t, int16x4_t> )
        return vreinterpret_s16_u16(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int8 -> ?
    else if constexpr( std::is_same_v<in_t, int8x8_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int16x8_t> )
        return vmovl_s8(v0);
      else if constexpr( std::is_same_v<tgt_t, uint16x8_t> )
        return vreinterpretq_u16_s16(vmovl_s8(v0));
      else if constexpr( std::is_same_v<tgt_t, uint8x8_t> )
        return vreinterpret_u8_s8(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint8 -> ?
    else if constexpr( std::is_same_v<in_t, uint8x8_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int16x8_t> )
        return vreinterpretq_s16_u16(vmovl_u8(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x8_t> )
        return vmovl_u8(v0);
      else if constexpr( std::is_same_v<tgt_t, int8x8_t> )
        return vreinterpret_s8_u8(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // other -> ?
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>
                  convert_(EVE_SUPPORTS(neon128_), wide<T, N, arm_128_> const &v0, as_<U> const &tgt) noexcept
  {
    using in_t  = typename wide<T, N, arm_128_>::storage_type;
    using tgt_t = typename wide<U, N>::storage_type;

    // Idempotent call
    if constexpr( std::is_same_v<T, U> )
      return v0;

#if defined(__aarch64__)
    //==============================================================================================
    // double -> ?
    if constexpr( std::is_same_v<in_t, float64x2_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int64x2_t> )
        return vcvtq_s64_f64(v0);
      else if constexpr( std::is_same_v<tgt_t, uint64x2_t> )
        return vcvtq_u64_f64(v0);
      else if constexpr( std::is_same_v<tgt_t, int32x2_t> )
        return vmovn_s64(vcvtq_s64_f64(v0));
      else if constexpr( std::is_same_v<tgt_t, uint32x2_t> )
        return vmovn_u64(vcvtq_u64_f64(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
#endif
    //==============================================================================================
    // float -> ?
    if constexpr( std::is_same_v<in_t, float32x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vcvtq_s32_f32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vcvtq_u32_f32(v0);
      else if constexpr( std::is_same_v<tgt_t, int16x4_t> )
        return vmovn_s32(vcvtq_s32_f32(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x4_t> )
        return vmovn_u32(vcvtq_u32_f32(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int64 -> ?
    else if constexpr( std::is_same_v<in_t, int64x2_t> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<tgt_t, float64x2_t> )
        return vcvtq_f64_s64(v0);
#endif
      if constexpr( std::is_same_v<tgt_t, uint64x2_t> )
        return vreinterpretq_u64_s64(v0);
      else if constexpr( std::is_same_v<tgt_t, float32x2_t> )
        return vcvt_f32_s32(vmovn_s64(v0));
      else if constexpr( std::is_same_v<tgt_t, int32x2_t> )
        return vmovn_s64(v0);
      else if constexpr( std::is_same_v<tgt_t, uint32x2_t> )
        return vreinterpret_u32_s32(vmovn_s64(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint64 -> ?
    else if constexpr( std::is_same_v<in_t, uint64x2_t> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<tgt_t, float64x2_t> )
        return vcvtq_f64_u64(v0);
#endif
      if constexpr( std::is_same_v<tgt_t, int64x2_t> )
        return vreinterpretq_s64_u64(v0);
      else if constexpr( std::is_same_v<tgt_t, float32x2_t> )
        return vcvt_f32_u32(vmovn_u64(v0));
      else if constexpr( std::is_same_v<tgt_t, uint32x2_t> )
        return vmovn_u64(v0);
      else if constexpr( std::is_same_v<tgt_t, int32x2_t> )
        return vreinterpret_s32_u32(vmovn_u64(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int32 -> ?
    else if constexpr( std::is_same_v<in_t, int32x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vreinterpretq_u32_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, int16x4_t> )
        return vmovn_s32(v0);
      else if constexpr( std::is_same_v<tgt_t, uint16x4_t> )
        return vreinterpret_u16_s16(vmovn_s32(v0));
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint32 -> ?
    else if constexpr( std::is_same_v<in_t, uint32x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_u32(v0);
      else if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vreinterpretq_s32_u32(v0);
      else if constexpr( std::is_same_v<tgt_t, int16x4_t> )
        return vreinterpret_s16_u16(vmovn_u32(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x4_t> )
        return vmovn_u32(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int16 -> ?
    else if constexpr( std::is_same_v<in_t, int16x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vreinterpretq_u32_s32(vmovl_s16(v0));
      else if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vmovl_s16(v0);
      else if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_s32(movl_s16(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x4_t> )
        return vreinterpret_u16_s16(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint16 -> ?
    else if constexpr( std::is_same_v<in_t, uint16x4_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int32x4_t> )
        return vreinterpretq_s32_u32(vmovl_u16(v0));
      else if constexpr( std::is_same_v<tgt_t, uint32x4_t> )
        return vmovl_u16(v0);
      else if constexpr( std::is_same_v<tgt_t, float32x4_t> )
        return vcvtq_f32_u32(movl_u16(v0));
      else if constexpr( std::is_same_v<tgt_t, int16x4_t> )
        return vreinterpret_s16_u16(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int8 -> ?
    else if constexpr( std::is_same_v<in_t, int8x8_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int16x8_t> )
        return vmovl_s8(v0);
      else if constexpr( std::is_same_v<tgt_t, uint16x8_t> )
        return vreinterpretq_u16_s16(vmovl_s8(v0));
      else if constexpr( std::is_same_v<tgt_t, uint8x8_t> )
        return vreinterpret_u8_s8(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint8 -> ?
    else if constexpr( std::is_same_v<in_t, uint8x8_t> )
    {
      if constexpr( std::is_same_v<tgt_t, int16x8_t> )
        return vreinterpretq_s16_u16(vmovl_u8(v0));
      else if constexpr( std::is_same_v<tgt_t, uint16x8_t> )
        return vmovl_u8(v0);
      else if constexpr( std::is_same_v<tgt_t, int8x8_t> )
        return vreinterpret_s8_u8(v0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // other -> ?
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }
}

