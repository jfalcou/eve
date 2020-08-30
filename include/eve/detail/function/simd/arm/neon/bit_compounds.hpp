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

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, neon64_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon64_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon64_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitand(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpret_f32_u32(
            vand_u32(vreinterpret_u32_f32(self), vreinterpret_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpret_f64_u64(
            vand_u64(vreinterpret_u64_f64(self), vreinterpret_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vand_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vand_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vand_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vand_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vand_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vand_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vand_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vand_u8(self, bit_other);
        }
      }
    }

    return self;
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, neon128_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon128_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon128_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitand(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpretq_f32_u32(
            vandq_u32(vreinterpretq_u32_f32(self), vreinterpretq_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpretq_f64_u64(
            vandq_u64(vreinterpretq_u64_f64(self), vreinterpretq_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vandq_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vandq_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vandq_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vandq_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vandq_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vandq_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vandq_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vandq_u8(self, bit_other);
        }
      }
    }

    return self;
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N, neon64_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon64_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon64_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpret_f32_u32(
            vorr_u32(vreinterpret_u32_f32(self), vreinterpret_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpret_f64_u64(
            vorr_u64(vreinterpret_u64_f64(self), vreinterpret_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vorr_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vorr_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vorr_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vorr_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vorr_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vorr_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vorr_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vorr_u8(self, bit_other);
        }
      }
    }

    return self;
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N, neon128_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon128_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon128_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpretq_f32_u32(
            vorrq_u32(vreinterpretq_u32_f32(self), vreinterpretq_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpretq_f64_u64(
            vorrq_u64(vreinterpretq_u64_f64(self), vreinterpretq_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vorrq_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vorrq_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vorrq_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vorrq_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vorrq_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vorrq_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vorrq_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vorrq_u8(self, bit_other);
        }
      }
    }

    return self;
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N, neon64_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon64_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon64_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpret_f32_u32(
            veor_u32(vreinterpret_u32_f32(self), vreinterpret_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpret_f64_u64(
            veor_u64(vreinterpret_u64_f64(self), vreinterpret_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = veor_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = veor_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = veor_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = veor_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = veor_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = veor_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = veor_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = veor_u8(self, bit_other);
        }
      }
    }

    return self;
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N, neon128_> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, neon128_>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, neon128_>;

    if constexpr( element_bit_compatible_to<U, type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      self           = self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});

      if constexpr( std::is_same_v<T, float> )
      {
        self = vreinterpretq_f32_u32(
            veorq_u32(vreinterpretq_u32_f32(self), vreinterpretq_u32_f32(bit_other)));
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vreinterpretq_f64_u64(
            veorq_u64(vreinterpretq_u64_f64(self), vreinterpretq_u64_f64(bit_other)));
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = veorq_s64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = veorq_s32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = veorq_s16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = veorq_s8(self, bit_other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = veorq_u64(self, bit_other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = veorq_u32(self, bit_other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = veorq_u16(self, bit_other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = veorq_u8(self, bit_other);
        }
      }
    }

    return self;
  }
}

