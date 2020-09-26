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
#include <eve/detail/concepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/forward.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI, typename Arch>
  EVE_FORCEINLINE auto load(eve::as_<wide<T, N, ABI>> const &, Arch const &, T const* ptr) noexcept
  {
    if constexpr( N::value * sizeof(T) >= arm_64_::bytes )
    {
      if constexpr( std::is_same_v<T, float> )
      {
              if constexpr( std::is_same_v<Arch, eve::arm_128_> ) return vld1q_f32(ptr);
        else  if constexpr( std::is_same_v<Arch, eve::arm_64_>  ) return vld1_f32(ptr);
      }
  #if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
              if constexpr( std::is_same_v<Arch, eve::arm_128_> ) return vld1q_f64(ptr);
        else  if constexpr( std::is_same_v<Arch, eve::arm_64_>  ) return vld1_f64(ptr);
      }
  #endif
      else if constexpr( std::signed_integral<T> )
      {
        if constexpr( std::is_same_v<Arch, eve::arm_128_> )
        {
          if constexpr( sizeof(T) == 8 )  return vld1q_s64(ptr);
          if constexpr( sizeof(T) == 4 )  return vld1q_s32(ptr);
          if constexpr( sizeof(T) == 2 )  return vld1q_s16(ptr);
          if constexpr( sizeof(T) == 1 )  return vld1q_s8(ptr);
        }
        else if constexpr( std::is_same_v<Arch, eve::arm_64_>  )
        {
          if constexpr( sizeof(T) == 8 ) return vld1_s64(ptr);
          if constexpr( sizeof(T) == 4 ) return vld1_s32(ptr);
          if constexpr( sizeof(T) == 2 ) return vld1_s16(ptr);
          if constexpr( sizeof(T) == 1 ) return vld1_s8(ptr);
        }
      }
      else
      {
        if constexpr( std::is_same_v<Arch, eve::arm_128_> )
        {
          if constexpr( sizeof(T) == 8 )  return vld1q_u64(ptr);
          if constexpr( sizeof(T) == 4 )  return vld1q_u32(ptr);
          if constexpr( sizeof(T) == 2 )  return vld1q_u16(ptr);
          if constexpr( sizeof(T) == 1 )  return vld1q_u8(ptr);
        }
        else if constexpr( std::is_same_v<Arch, eve::arm_64_>  )
        {
          if constexpr( sizeof(T) == 8 ) return vld1_u64(ptr);
          if constexpr( sizeof(T) == 4 ) return vld1_u32(ptr);
          if constexpr( sizeof(T) == 2 ) return vld1_u16(ptr);
          if constexpr( sizeof(T) == 1 ) return vld1_u8(ptr);
        }
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
  template<real_scalar_value T, typename N, arm_abi ABI, typename Arch>
  EVE_FORCEINLINE auto load ( as_<wide<T, N, ABI>> const &
                            , Arch const &, aligned_ptr<T const, Align> p
                            ) noexcept
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
        if constexpr( std::is_same_v<T, float> )
        {
                if constexpr( std::is_same_v<Arch, eve::arm_128_> ) return vld1q_f32_ex(ptr, 128);
          else  if constexpr( std::is_same_v<Arch, eve::arm_64_>  ) return vld1_f32_ex(ptr, 64);
        }
    #if defined(__aarch64__)
        else if constexpr( std::is_same_v<T, double> )
        {
                if constexpr( std::is_same_v<Arch, eve::arm_128_> ) return vld1q_f64_ex(ptr, 128);
          else  if constexpr( std::is_same_v<Arch, eve::arm_64_>  ) return vld1_f64_ex(ptr, 64);
        }
    #endif
        else if constexpr( std::signed_integral<T> )
        {
          if constexpr( std::is_same_v<Arch, eve::arm_128_> )
          {
            if constexpr( sizeof(T) == 8 )  return vld1q_s64_ex(ptr, 128);
            if constexpr( sizeof(T) == 4 )  return vld1q_s32_ex(ptr, 128);
            if constexpr( sizeof(T) == 2 )  return vld1q_s16_ex(ptr, 128);
            if constexpr( sizeof(T) == 1 )  return vld1q_s8_ex(ptr, 128);
          }
          else if constexpr( std::is_same_v<Arch, eve::arm_64_>  )
          {
            if constexpr( sizeof(T) == 8 ) return vld1_s64_ex(ptr, 64);
            if constexpr( sizeof(T) == 4 ) return vld1_s32_ex(ptr, 64);
            if constexpr( sizeof(T) == 2 ) return vld1_s16_ex(ptr, 64);
            if constexpr( sizeof(T) == 1 ) return vld1_s8_ex(ptr, 64);
          }
        }
        else
        {
          if constexpr( std::is_same_v<Arch, eve::arm_128_> )
          {
            if constexpr( sizeof(T) == 8 )  return vld1q_u64_ex(ptr, 128);
            if constexpr( sizeof(T) == 4 )  return vld1q_u32_ex(ptr, 128);
            if constexpr( sizeof(T) == 2 )  return vld1q_u16_ex(ptr, 128);
            if constexpr( sizeof(T) == 1 )  return vld1q_u8_ex(ptr, 128);
          }
          else if constexpr( std::is_same_v<Arch, eve::arm_64_>  )
          {
            if constexpr( sizeof(T) == 8 ) return vld1_u64_ex(ptr, 64);
            if constexpr( sizeof(T) == 4 ) return vld1_u32_ex(ptr, 64);
            if constexpr( sizeof(T) == 2 ) return vld1_u16_ex(ptr, 64);
            if constexpr( sizeof(T) == 1 ) return vld1_u8_ex(ptr, 64);
          }
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

  template<real_scalar_value T, typename N, typename Arch, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt,Arch const &, aligned_ptr<T, Align> p) noexcept
  {
    return load(tgt, mode, aligned_ptr<T const, A>(p));
  }

#else

  template<real_scalar_value T, typename N, typename Arch, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt, Arch const &  mode,aligned_ptr<T const, Align>  ptr)
  {
    return load(tgt, mode, ptr.get());
  }

  template<real_scalar_value T, typename N, typename Arch, arm_abi ABI, std::size_t Align>
  EVE_FORCEINLINE auto
  load(eve::as_<wide<T, N, ABI>> const &tgt, Arch const &mode, aligned_ptr<T, Align> ptr) noexcept
  {
    return load(tgt, mode, ptr.get());
  }
#endif
}
