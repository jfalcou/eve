//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#  pragma GCC diagnostic ignored "-Wdeprecated"
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &,
                            eve::neon128_ const &,
                            T *ptr) noexcept requires(typename wide<T, N>::storage_type,
                                                      vectorizable<T>)
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vld1q_f64(ptr);
#endif

    if constexpr(std::is_same_v<T, float>) return vld1q_f32(ptr);

    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 8) return vld1q_s64(ptr);
        if constexpr(sizeof(T) == 4) return vld1q_s32(ptr);
        if constexpr(sizeof(T) == 2) return vld1q_s16(ptr);
        if constexpr(sizeof(T) == 1) return vld1q_s8(ptr);
      }
      else
      {
        if constexpr(sizeof(T) == 8) return vld1q_u64(ptr);
        if constexpr(sizeof(T) == 4) return vld1q_u32(ptr);
        if constexpr(sizeof(T) == 2) return vld1q_u16(ptr);
        if constexpr(sizeof(T) == 1) return vld1q_u8(ptr);
      }
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &,
                            eve::neon64_ const &,
                            T *ptr) noexcept requires(typename wide<T, N>::storage_type,
                                                      vectorizable<T>)
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vld1_f64(ptr);
#endif

    if constexpr(std::is_same_v<T, float>) return vld1_f32(ptr);

    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 8) return vld1_s64(ptr);
        if constexpr(sizeof(T) == 4) return vld1_s32(ptr);
        if constexpr(sizeof(T) == 2) return vld1_s16(ptr);
        if constexpr(sizeof(T) == 1) return vld1_s8(ptr);
      }
      else
      {
        if constexpr(sizeof(T) == 8) return vld1_u64(ptr);
        if constexpr(sizeof(T) == 4) return vld1_u32(ptr);
        if constexpr(sizeof(T) == 2) return vld1_u16(ptr);
        if constexpr(sizeof(T) == 1) return vld1_u8(ptr);
      }
    }
  }

#if defined(EVE_COMP_IS_MSVC)
  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt,
       eve::neon128_ const &,
       aligned_ptr<T, Align> p) noexcept requires(typename wide<T, N>::storage_type,
                                                  vectorizable<T>)
  {
    auto ptr = p.get();

    if constexpr(Align < 16) { return load(ptr, tgt); }
    else
    {
      if constexpr(std::is_same_v<T, float>) return vld1q_f32_ex(ptr, 128);
#  if defined(__aarch64__)
      else if constexpr(std::is_same_v<T, double>)
        return vld1q_f64_ex(ptr, 128);
#  endif
      else if constexpr(std::is_integral_v<T>)
      {
        if constexpr(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 8)
            return vld1q_s64_ex(ptr, 128);
          else if constexpr(sizeof(T) == 4)
            return vld1q_s32_ex(ptr, 128);
          else if constexpr(sizeof(T) == 2)
            return vld1q_s16_ex(ptr, 128);
          else if constexpr(sizeof(T) == 1)
            return vld1q_s8_ex(ptr, 128);
        }
        else
        {
          if constexpr(sizeof(T) == 8)
            return vld1q_u64_ex(ptr, 128);
          else if constexpr(sizeof(T) == 4)
            return vld1q_u32_ex(ptr, 128);
          else if constexpr(sizeof(T) == 2)
            return vld1q_u16_ex(ptr, 128);
          else if constexpr(sizeof(T) == 1)
            return vld1q_u8_ex(ptr, 128);
        }
      }
    }
  }

  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &,
       eve::neon64_ const &,
       aligned_ptr<T, Align> p) noexcept requires(typename wide<T, N>::storage_type,
                                                  vectorizable<T>)
  {
    auto ptr = p.get();

    if constexpr(Align < 8) { return load(ptr, tgt); }
    else
    {
      if constexpr(std::is_same_v<T, float>) return vld1_f32_ex(ptr, 64);
#  if defined(__aarch64__)
      else if constexpr(std::is_same_v<T, double>)
        return vld1_f64_ex(ptr, 64);
#  endif
      else if constexpr(std::is_integral_v<T>)
      {
        if constexpr(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 8)
            return vld1_s64_ex(ptr, 64);
          else if constexpr(sizeof(T) == 4)
            return vld1_s32_ex(ptr, 64);
          else if constexpr(sizeof(T) == 2)
            return vld1_s16_ex(ptr, 64);
          else if constexpr(sizeof(T) == 1)
            return vld1_s8_ex(ptr, 64);
        }
        else
        {
          if constexpr(sizeof(T) == 8)
            return vld1_u64_ex(ptr, 64);
          else if constexpr(sizeof(T) == 4)
            return vld1_u32_ex(ptr, 64);
          else if constexpr(sizeof(T) == 2)
            return vld1_u16_ex(ptr, 64);
          else if constexpr(sizeof(T) == 1)
            return vld1_u8_ex(ptr, 64);
        }
      }
    }
  }
#else
  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt,
       eve::neon128_ const &  mode,
       aligned_ptr<T, Align>  ptr) noexcept requires(typename wide<T, N>::storage_type,
                                                    vectorizable<T>)
  {
    return load(tgt, mode, ptr.get());
  }

  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt,
       eve::neon64_ const &   mode,
       aligned_ptr<T, Align>  ptr) noexcept requires(typename wide<T, N>::storage_type,
                                                    vectorizable<T>)
  {
    return load(tgt, mode, ptr.get());
  }
#endif
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
