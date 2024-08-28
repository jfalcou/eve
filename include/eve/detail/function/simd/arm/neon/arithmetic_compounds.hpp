//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/skeleton.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // *=
  //================================================================================================
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && arm_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;
    constexpr auto c = categorize<type>();

    if constexpr( plain_scalar_value<U> )
    {
            if constexpr( c == category::int32x2    ) self = vmul_n_s32 (self, other);
      else  if constexpr( c == category::int32x4    ) self = vmulq_n_s32(self, other);
      else  if constexpr( c == category::uint32x2   ) self = vmul_n_u32 (self, other);
      else  if constexpr( c == category::uint32x4   ) self = vmulq_n_u32(self, other);
      else  if constexpr( c == category::int16x4    ) self = vmul_n_s16 (self, other);
      else  if constexpr( c == category::int16x8    ) self = vmulq_n_s16(self, other);
      else  if constexpr( c == category::uint16x4   ) self = vmul_n_u16 (self, other);
      else  if constexpr( c == category::uint16x8   ) self = vmulq_n_u16(self, other);
      else  if constexpr( c == category::int8x8     ) self = vmul_s8    (self, type(other));
      else  if constexpr( c == category::int8x16    ) self = vmulq_s8   (self, type(other));
      else  if constexpr( c == category::uint8x8    ) self = vmul_u8    (self, type(other));
      else  if constexpr( c == category::uint8x16   ) self = vmulq_u8   (self, type(other));
      else  if constexpr( c == category::float32x2  ) self = vmul_n_f32 (self, other);
      else  if constexpr( c == category::float32x4  ) self = vmulq_n_f32(self, other);
      else if constexpr( current_api >= asimd )
      {
              if constexpr( c == category::float64x1 ) self = vmul_n_f64  (self, other);
        else  if constexpr( c == category::float64x2 ) self = vmulq_n_f64 (self, other);
        else  apply<N::value>([&](auto... I) { (self.set(I, self.get(I) * other), ...); });
      }
      else  apply<N::value>([&](auto... I) { (self.set(I, self.get(I) * other), ...); });
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr( c == category::int32x2    ) self = vmul_s32 (self, other);
      else  if constexpr( c == category::int32x4    ) self = vmulq_s32(self, other);
      else  if constexpr( c == category::uint32x2   ) self = vmul_u32 (self, other);
      else  if constexpr( c == category::uint32x4   ) self = vmulq_u32(self, other);
      else  if constexpr( c == category::int16x4    ) self = vmul_s16 (self, other);
      else  if constexpr( c == category::int16x8    ) self = vmulq_s16(self, other);
      else  if constexpr( c == category::uint16x4   ) self = vmul_u16 (self, other);
      else  if constexpr( c == category::uint16x8   ) self = vmulq_u16(self, other);
      else  if constexpr( c == category::int8x8     ) self = vmul_s8  (self, other);
      else  if constexpr( c == category::int8x16    ) self = vmulq_s8 (self, other);
      else  if constexpr( c == category::uint8x8    ) self = vmul_u8  (self, other);
      else  if constexpr( c == category::uint8x16   ) self = vmulq_u8 (self, other);
      else  if constexpr( c == category::float32x2  ) self = vmul_f32 (self, other);
      else  if constexpr( c == category::float32x4  ) self = vmulq_f32(self, other);
      else if constexpr( current_api >= asimd )
      {
              if constexpr( c == category::float64x1 ) self = vmul_f64  (self, other);
        else  if constexpr( c == category::float64x2 ) self = vmulq_f64 (self, other);
        else  apply<N::value>([&](auto... I) { (self.set(I, self.get(I) * other.get(I)), ...); });
      }
      else  apply<N::value>([&](auto... I) { (self.set(I, self.get(I) * other.get(I)), ...); });
    }

    return self;
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && arm_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
    {
      self = self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( current_api >= asimd)
      {
        constexpr auto c = categorize<type>();

              if constexpr( c == category::float64x1 )  self = vdiv_f64 (self, other);
        else  if constexpr( c == category::float64x2 )  self = vdivq_f64(self, other);
        else  if constexpr( c == category::float32x2 )  self = vdiv_f32 (self, other);
        else  if constexpr( c == category::float32x4 )  self = vdivq_f32(self, other);
        else  apply<N::value>([&](auto... I) {(self.set(I,self.get(I)/other.get(I)), ...);});
      }
      else if constexpr( std::same_as<T, float> )
      {
        auto estimate = [](auto x)
        {
          constexpr auto c = categorize<type>();
                if constexpr( c == category::float32x2 ) return vrecpe_f32(x);
          else  if constexpr( c == category::float32x4 ) return vrecpeq_f32(x);
        };

        auto refine = [](auto x, auto y) -> type
        {
          constexpr auto c = categorize<type>();
                if constexpr( c == category::float32x2 ) return vmul_f32(vrecps_f32(x, y), y);
          else  if constexpr( c == category::float32x4 ) return vmulq_f32(vrecpsq_f32(x, y), y);
        };

        self *= refine(other, refine(other, estimate(other)));
      }
      else if constexpr( current_api >= asimd && std::same_as<T, double> )
      {
        auto estimate = [](auto x)
        {
          constexpr auto c = categorize<type>();
                if constexpr( c == category::float64x1 ) return vrecpe_f64(x);
          else  if constexpr( c == category::float64x2 ) return vrecpeq_f64(x);
        };

        auto refine = [](auto x, auto y) -> type
        {
          constexpr auto c = categorize<type>();
                if constexpr( c == category::float64x1 ) return vmul_f64(vrecps_f64(x, y), y);
          else  if constexpr( c == category::float64x2 ) return vmulq_f64(vrecpsq_f64(x, y), y);
        };

        self *= refine(other, refine(other, estimate(other)));
      }
      else
      {
        apply<N::value>([&](auto... I) { (self.set(I, self.get(I) / other.get(I)), ...); });
      }
    }

    return self;
  }
}
