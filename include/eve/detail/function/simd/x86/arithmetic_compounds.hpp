//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr  ( c == category::float64x8  ) self = _mm512_add_pd(self, other);
      else  if constexpr  ( c == category::float32x16 ) self = _mm512_add_ps(self, other);
      else  if constexpr  ( c == category::int64x8    ) self = _mm512_add_epi64(self, other);
      else  if constexpr  ( c == category::int32x16   ) self = _mm512_add_epi32(self, other);
      else  if constexpr  ( c == category::int16x32   ) self = _mm512_add_epi16(self, other);
      else  if constexpr  ( c == category::int8x64    ) self = _mm512_add_epi8(self, other);
      else  if constexpr  ( c == category::uint64x8   ) self = _mm512_add_epi64(self, other);
      else  if constexpr  ( c == category::uint32x16  ) self = _mm512_add_epi32(self, other);
      else  if constexpr  ( c == category::uint16x32  ) self = _mm512_add_epi16(self, other);
      else  if constexpr  ( c == category::uint8x64   ) self = _mm512_add_epi8(self, other);
      else  if constexpr  ( c == category::float64x2  ) self = _mm_add_pd(self, other);
      else  if constexpr  ( c == category::float32x4  ) self = _mm_add_ps(self, other);
      else  if constexpr  ( c == category::int64x2    ) self = _mm_add_epi64(self, other);
      else  if constexpr  ( c == category::int32x4    ) self = _mm_add_epi32(self, other);
      else  if constexpr  ( c == category::int16x8    ) self = _mm_add_epi16(self, other);
      else  if constexpr  ( c == category::int8x16    ) self = _mm_add_epi8(self, other);
      else  if constexpr  ( c == category::uint64x2   ) self = _mm_add_epi64(self, other);
      else  if constexpr  ( c == category::uint32x4   ) self = _mm_add_epi32(self, other);
      else  if constexpr  ( c == category::uint16x8   ) self = _mm_add_epi16(self, other);
      else  if constexpr  ( c == category::uint8x16   ) self = _mm_add_epi8(self, other);
      else  if constexpr  ( c == category::float64x4  ) self = _mm256_add_pd(self, other);
      else  if constexpr  ( c == category::float32x8  ) self = _mm256_add_ps(self, other);
      else  if constexpr  ( current_api >= avx2 )
      {
              if constexpr  ( c == category::int64x4  ) self = _mm256_add_epi64(self, other);
        else  if constexpr  ( c == category::uint64x4 ) self = _mm256_add_epi64(self, other);
        else  if constexpr  ( c == category::int32x8  ) self = _mm256_add_epi32(self, other);
        else  if constexpr  ( c == category::uint32x8 ) self = _mm256_add_epi32(self, other);
        else  if constexpr  ( c == category::int16x16 ) self = _mm256_add_epi16(self, other);
        else  if constexpr  ( c == category::uint16x16) self = _mm256_add_epi16(self, other);
        else  if constexpr  ( c == category::int8x32  ) self = _mm256_add_epi8(self, other);
        else  if constexpr  ( c == category::uint8x32 ) self = _mm256_add_epi8(self, other);
      }
      else
      {
        auto [s1, s2] = self.slice();
        auto [o1, o2] = other.slice();
        s1 += o1;
        s2 += o2;
        self = type {s1, s2};
      }

      return self;
    }
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self_sub(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr  ( c == category::float64x8  ) self = _mm512_sub_pd(self, other);
      else  if constexpr  ( c == category::float32x16 ) self = _mm512_sub_ps(self, other);
      else  if constexpr  ( c == category::int64x8    ) self = _mm512_sub_epi64(self, other);
      else  if constexpr  ( c == category::int32x16   ) self = _mm512_sub_epi32(self, other);
      else  if constexpr  ( c == category::int16x32   ) self = _mm512_sub_epi16(self, other);
      else  if constexpr  ( c == category::int8x64    ) self = _mm512_sub_epi8(self, other);
      else  if constexpr  ( c == category::uint64x8   ) self = _mm512_sub_epi64(self, other);
      else  if constexpr  ( c == category::uint32x16  ) self = _mm512_sub_epi32(self, other);
      else  if constexpr  ( c == category::uint16x32  ) self = _mm512_sub_epi16(self, other);
      else  if constexpr  ( c == category::uint8x64   ) self = _mm512_sub_epi8(self, other);
      else  if constexpr  ( c == category::float64x2  ) self = _mm_sub_pd(self, other);
      else  if constexpr  ( c == category::float32x4  ) self = _mm_sub_ps(self, other);
      else  if constexpr  ( c == category::int64x2    ) self = _mm_sub_epi64(self, other);
      else  if constexpr  ( c == category::int32x4    ) self = _mm_sub_epi32(self, other);
      else  if constexpr  ( c == category::int16x8    ) self = _mm_sub_epi16(self, other);
      else  if constexpr  ( c == category::int8x16    ) self = _mm_sub_epi8(self, other);
      else  if constexpr  ( c == category::uint64x2   ) self = _mm_sub_epi64(self, other);
      else  if constexpr  ( c == category::uint32x4   ) self = _mm_sub_epi32(self, other);
      else  if constexpr  ( c == category::uint16x8   ) self = _mm_sub_epi16(self, other);
      else  if constexpr  ( c == category::uint8x16   ) self = _mm_sub_epi8(self, other);
      else  if constexpr  ( c == category::float64x4  ) self = _mm256_sub_pd(self, other);
      else  if constexpr  ( c == category::float32x8  ) self = _mm256_sub_ps(self, other);
      else  if constexpr  ( current_api >= avx2 )
      {
              if constexpr  ( c == category::int64x4  ) self = _mm256_sub_epi64(self, other);
        else  if constexpr  ( c == category::uint64x4 ) self = _mm256_sub_epi64(self, other);
        else  if constexpr  ( c == category::int32x8  ) self = _mm256_sub_epi32(self, other);
        else  if constexpr  ( c == category::uint32x8 ) self = _mm256_sub_epi32(self, other);
        else  if constexpr  ( c == category::int16x16 ) self = _mm256_sub_epi16(self, other);
        else  if constexpr  ( c == category::uint16x16) self = _mm256_sub_epi16(self, other);
        else  if constexpr  ( c == category::int8x32  ) self = _mm256_sub_epi8(self, other);
        else  if constexpr  ( c == category::uint8x32 ) self = _mm256_sub_epi8(self, other);
      }
      else
      {
        auto [s1, s2] = self.slice();
        auto [o1, o2] = other.slice();
        s1 -= o1;
        s2 -= o2;
        self = type {s1, s2};
      }

      return self;
    }
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self_mul(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr( c == category::float64x8  ) self = _mm512_mul_pd(self, other);
      else  if constexpr( c == category::float64x4  ) self = _mm256_mul_pd(self, other);
      else  if constexpr( c == category::float64x2  ) self = _mm_mul_pd(self, other);
      else  if constexpr( c == category::float32x16 ) self = _mm512_mul_ps(self, other);
      else  if constexpr( c == category::float32x8  ) self = _mm256_mul_ps(self, other);
      else  if constexpr( c == category::float32x4  ) self = _mm_mul_ps(self, other);
      else  if constexpr( c == category::int64x8    ) self = _mm512_mullo_epi64(self, other);
      else  if constexpr( c == category::uint64x8   ) self = _mm512_mullo_epi64(self, other);
      else  if constexpr( c == category::int32x16   ) self = _mm512_mullo_epi32(self, other);
      else  if constexpr( c == category::uint32x16  ) self = _mm512_mullo_epi32(self, other);
      else  if constexpr((c == category::int32x8 || c == category::uint32x8) && current_api >= avx2)
      {
        self = _mm256_mullo_epi32(self, other);
      }
      else  if constexpr( c == category::int32x4 || c == category::uint32x4 )
      {
        if constexpr( current_api >= sse4_1 )
        {
          self = _mm_mullo_epi32(self, other);
        }
        else
        {
          using htype  = wide<std::int64_t, fixed<N::value / 2>>;
          htype mhi    = _mm_setr_epi32(-1, 0, -1, 0);
          htype mlo    = mhi;
          auto  lself  = _mm_srli_si128(self, 4);
          auto  lother = _mm_srli_si128(other, 4);

          mhi &= htype {_mm_mul_epu32(self, other)};
          mlo &= htype {_mm_mul_epu32(lself, lother)};
          mhi |= htype {_mm_slli_si128(mlo, 4)};
          self = mhi.storage();
        }
      }
      else  if constexpr((c == category::int16x16 || c == category::uint16x16) && current_api >= avx2)
      {
        self = _mm256_mullo_epi16(self, other);
      }
      else  if constexpr( c == category::int16x32   ) self = _mm512_mullo_epi16(self, other);
      else  if constexpr( c == category::uint16x32  ) self = _mm512_mullo_epi16(self, other);
      else  if constexpr( c == category::int16x8    ) self = _mm_mullo_epi16(self, other);
      else  if constexpr( c == category::uint16x8   ) self = _mm_mullo_epi16(self, other);
      else  if constexpr( c == category::int8x16 || c == category::uint8x16 )
      {
        using htype  = wide<std::int16_t, fixed<N::value / 2>>;
        htype mhi    = _mm_set1_epi16(0x00FF);
        htype mlo    = mhi;
        auto  lself  = _mm_srli_epi16(self, 8);
        auto  lother = _mm_srli_epi16(other, 8);

        mhi &= htype {_mm_mullo_epi16(self, other)};
        mlo &= htype {_mm_mullo_epi16(lself, lother)};
        mhi |= htype {_mm_slli_epi16(mlo, 8)};
        self = mhi.storage();
      }
      else
      {
        auto s = self;
        constexpr auto smul = [](auto a, auto b) { return a *= b; };
        if constexpr( N::value >= 2  )  self = aggregate(smul, s, other);
        else                            self = map(smul, s, other);
      }

      return self;
    }
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr  ( c == category::float64x8  ) self = _mm512_div_pd(self, other);
      else  if constexpr  ( c == category::float64x4  ) self = _mm256_div_pd(self, other);
      else  if constexpr  ( c == category::float64x2  ) self = _mm_div_pd(self, other);
      else  if constexpr  ( c == category::float32x16 ) self = _mm512_div_ps(self, other);
      else  if constexpr  ( c == category::float32x8  ) self = _mm256_div_ps(self, other);
      else  if constexpr  ( c == category::float32x4  ) self = _mm_div_ps(self, other);
      else  if constexpr  ( c == category::int32x4 && current_api >= avx  )
      {
        auto dividend = _mm256_cvtepi32_pd(self);
        auto divisor  = _mm256_cvtepi32_pd(other);
        self = _mm256_cvttpd_epi32(_mm256_div_pd(dividend, divisor));
      }
      else
      {
        auto s = self;
        constexpr auto sdiv = [](auto a, auto b) { return a /= b; };
        if constexpr( N::value >= 2  )  self = aggregate(sdiv, s, other);
        else                            self = map(sdiv, s, other);
      }

      return self;
    }
  }
}
