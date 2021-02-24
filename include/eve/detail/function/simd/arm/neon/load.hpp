//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/forward.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto load(eve::as_<wide<T, N, ABI>> const &, T const* ptr) noexcept
  {
    if constexpr( N::value * sizeof(T) >= arm_64_::bytes )
    {
      constexpr auto c = categorize<wide<T, N, ABI>>();

            if constexpr( c == category::float32x4 )  return vld1q_f32(ptr);
      else  if constexpr( c == category::float32x2 )  return vld1_f32(ptr);
      else  if constexpr( c == category::int64x2  )   return vld1q_s64(ptr);
      else  if constexpr( c == category::int64x1  )   return vld1_s64(ptr);
      else  if constexpr( c == category::uint64x2 )   return vld1q_u64(ptr);
      else  if constexpr( c == category::uint64x1 )   return vld1_u64(ptr);
      else  if constexpr( c == category::int32x4  )   return vld1q_s32(ptr);
      else  if constexpr( c == category::int32x2  )   return vld1_s32(ptr);
      else  if constexpr( c == category::uint32x4 )   return vld1q_u32(ptr);
      else  if constexpr( c == category::uint32x2 )   return vld1_u32(ptr);
      else  if constexpr( c == category::int16x8  )   return vld1q_s16(ptr);
      else  if constexpr( c == category::int16x4  )   return vld1_s16(ptr);
      else  if constexpr( c == category::uint16x8 )   return vld1q_u16(ptr);
      else  if constexpr( c == category::uint16x4 )   return vld1_u16(ptr);
      else  if constexpr( c == category::int8x16  )   return vld1q_s8(ptr);
      else  if constexpr( c == category::int8x8   )   return vld1_s8(ptr);
      else  if constexpr( c == category::uint8x16 )   return vld1q_u8(ptr);
      else  if constexpr( c == category::uint8x8  )   return vld1_u8(ptr);
      else if constexpr( current_api >= asimd)
      {
              if constexpr( c == category::float64x2 )  return vld1q_f64(ptr);
        else  if constexpr( c == category::float64x1 )  return vld1_f64(ptr);
      }
    }
    else
    {
      typename wide<T, N>::storage_type that;
      std::memcpy(&that, ptr, N::value * sizeof(T));
      return that;
    }
  }

#if defined(SPY_COMPILER_IS_MSVC)
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto load ( as_<wide<T, N, ABI>> const &, aligned_ptr<T const, Align> p) noexcept
  {
    auto ptr = p.get();

    if constexpr( Align < 16 )
    {
      return load(ptr, tgt);
    }
    else
    {
      if constexpr( N::value * sizeof(T) >= eve::arm_64_::bytes )
      {
        constexpr auto c = categorize<wide<T, N, ABI>>();

              if constexpr( c == category::float32x4 )  return vld1q_f32_ex(ptr,128);
        else  if constexpr( c == category::float32x2 )  return vld1_f32_ex(ptr,64);
        else  if constexpr( c == category::int64x2  )   return vld1q_s64_ex(ptr,128);
        else  if constexpr( c == category::int64x1  )   return vld1_s64_ex(ptr,64);
        else  if constexpr( c == category::uint64x2 )   return vld1q_u64_ex(ptr,128);
        else  if constexpr( c == category::uint64x1 )   return vld1_u64_ex(ptr,64);
        else  if constexpr( c == category::int32x4  )   return vld1q_s32_ex(ptr,128);
        else  if constexpr( c == category::int32x2  )   return vld1_s32_ex(ptr,64);
        else  if constexpr( c == category::uint32x4 )   return vld1q_u32_ex(ptr,128);
        else  if constexpr( c == category::uint32x2 )   return vld1_u32_ex(ptr,64);
        else  if constexpr( c == category::int16x8  )   return vld1q_s16_ex(ptr,128);
        else  if constexpr( c == category::int16x4  )   return vld1_s16_ex(ptr,64);
        else  if constexpr( c == category::uint16x8 )   return vld1q_u16_ex(ptr,128);
        else  if constexpr( c == category::uint16x4 )   return vld1_u16_ex(ptr,64);
        else  if constexpr( c == category::int8x16  )   return vld1q_s8_ex(ptr,128);
        else  if constexpr( c == category::int8x8   )   return vld1_s8_ex(ptr,64);
        else  if constexpr( c == category::uint8x16 )   return vld1q_u8_ex(ptr,128);
        else  if constexpr( c == category::uint8x8  )   return vld1_u8_ex(ptr,64);
        else if constexpr( current_api >= asimd)
        {
                if constexpr( c == category::float64x2 )  return vld1q_f64_ex(ptr,128);
          else  if constexpr( c == category::float64x1 )  return vld1_f64_ex(ptr,64);
        }
      }
      else
      {
        typename wide<T, N>::storage_type that;
        std::memcpy(&that, ptr, N::value * sizeof(T));
        return that;
      }
    }
  }

  template<real_scalar_value T, typename N, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt, aligned_ptr<T, Align> p) noexcept
  {
    return load(tgt, aligned_ptr<T const, A>(p));
  }

#else

  template<real_scalar_value T, typename N, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt,aligned_ptr<T const, Align>  ptr)
  {
    return load(tgt, ptr.get());
  }

  template<real_scalar_value T, typename N, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt, aligned_ptr<T, Align> ptr) noexcept
  {
    return load(tgt, ptr.get());
  }
#endif
}
