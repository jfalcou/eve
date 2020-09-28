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
#include <eve/detail/skeleton.hpp>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add(wide<T, N, arm_64_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_64_>, U>)
  {
    using type = wide<T, N, arm_64_>;

    if constexpr( scalar_value<U> )
    {
      self = self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vadd_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vadd_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vadd_s64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vadd_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vadd_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vadd_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vadd_u64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vadd_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vadd_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vadd_u8(self, other);
        }
      }
    }

    return self;
  }

  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add(wide<T, N, arm_128_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_128_>, U>)
  {
    using type = wide<T, N, arm_128_>;

    if constexpr( scalar_value<U> )
    {
      self = self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vaddq_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vaddq_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vaddq_s64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vaddq_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vaddq_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vaddq_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vaddq_u64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vaddq_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vaddq_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vaddq_u8(self, other);
        }
      }
    }

    return self;
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub(wide<T, N, arm_64_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_64_>, U>)
  {
    using type = wide<T, N, arm_64_>;

    if constexpr( scalar_value<U> )
    {
      self = self_sub(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vsub_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vsub_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vsub_s64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vsub_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vsub_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vsub_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vsub_u64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vsub_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vsub_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vsub_u8(self, other);
        }
      }
    }

    return self;
  }

  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub(wide<T, N, arm_128_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_128_>, U>)
  {
    using type = wide<T, N, arm_128_>;

    if constexpr( scalar_value<U> )
    {
      self = self_sub(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vsubq_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vsubq_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vsubq_s64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vsubq_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vsubq_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vsubq_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          self = vsubq_u64(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vsubq_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vsubq_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vsubq_u8(self, other);
        }
      }
    }

    return self;
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N, arm_64_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_64_>, U>)
  {
    using type = wide<T, N, arm_64_>;

    if constexpr( scalar_value<U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vmul_n_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vmul_n_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmul_n_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmul_n_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmul_s8(self, type {other});
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmul_n_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmul_n_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmul_u8(self, type {other});
        }
      }
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vmul_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vmul_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmul_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmul_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmul_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmul_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmul_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmul_u8(self, other);
        }
      }
    }

    return self;
  }

  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N, arm_128_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_128_>, U>)
  {
    using type = wide<T, N, arm_128_>;

    if constexpr( scalar_value<U> )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        self = vmulq_n_f32(self, other);
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        self = vmulq_n_f64(self, other);
      }
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmulq_n_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmulq_n_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmulq_s8(self, type {other});
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmulq_n_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmulq_n_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmulq_u8(self, type {other});
        }
      }
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, float> )
        self = vmulq_f32(self, other);
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
        self = vmulq_f64(self, other);
#endif
      else if constexpr( signed_integral_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmulq_s32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmulq_s16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmulq_s8(self, other);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = vmulq_u32(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = vmulq_u16(self, other);
        }
        else if constexpr( sizeof(T) == 1 )
        {
          self = vmulq_u8(self, other);
        }
      }
    }

    return self;
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N, arm_64_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_64_>, U>)
  {
    using type = wide<T, N, arm_64_>;

    if constexpr( scalar_value<U> )
    {
      self = self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<T, double> )
      {
        self = vdiv_f64(self, other);
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        self = vdiv_f32(self, other);
      }
#else
      if constexpr( std::is_same_v<T, float> )
      {
        // estimate 1/x with an extra NR step for full precision
        auto refiner = [](auto x, auto y) { return vmul_f32(vrecps_f32(x, y), y); };
        self *= refiner(other, refiner(other, vrecpe_f32(other)));
      }
#endif
      else
      {
        apply<N::value>([&](auto... I) { (self.set(I, self[I] / other[I]), ...); });
      }
    }

    return self;
  }

  template<real_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N, arm_128_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, arm_128_>, U>)
  {
    using type = wide<T, N, arm_128_>;

    if constexpr( scalar_value<U> )
    {
      self = self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
#if defined(__aarch64__)
      if constexpr( std::is_same_v<T, double> )
      {
        self = vdivq_f64(self, other);
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        self = vdivq_f32(self, other);
      }
#else
      if constexpr( std::is_same_v<T, float> )
      {
        // estimate 1/x with an extra NR step for full precision
        auto refiner = [](auto x, auto y) { return vmulq_f32(vrecpsq_f32(x, y), y); };
        self *= refiner(other, refiner(other, vrecpeq_f32(other)));
      }
#endif
      else
      {
        apply<N::value>([&](auto... I) { (self.set(I, self[I] / other[I]), ...); });
      }
    }

    return self;
  }
}

