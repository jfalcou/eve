//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_ARITHMETIC_COMPOUNDS_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_ARITHMETIC_COMPOUNDS_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <concepts>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>

// TODO: std:bitcast instead
#include <eve/module/core/function/generic/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add(wide<T, N, sse_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, sse_>, U>)
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      return self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm_add_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm_add_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          self = _mm_add_epi8(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = _mm_add_epi16(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = _mm_add_epi32(self, other);
        }
        else if constexpr( sizeof(T) == 8 )
        {
          self = _mm_add_epi64(self, other);
        }
      }
      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add(wide<T, N, avx_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, avx_>, U>)
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      return self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm256_add_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm256_add_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        if constexpr( current_api >= avx2 )
        {
          if constexpr( sizeof(T) == 1 )
          {
            self = _mm256_add_epi8(self, other);
          }
          else if constexpr( sizeof(T) == 2 )
          {
            self = _mm256_add_epi16(self, other);
          }
          else if constexpr( sizeof(T) == 4 )
          {
            self = _mm256_add_epi32(self, other);
          }
          else if constexpr( sizeof(T) == 8 )
          {
            self = _mm256_add_epi64(self, other);
          }
        }
        else
        {
          auto [s1, s2] = self.slice();
          auto [o1, o2] = other.slice();
          s1 += o1;
          s2 += o2;
          self = type {s1, s2};
        }
      }
      return self;
    }
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub(wide<T, N, sse_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, sse_>, U>)
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      return self_sub(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm_sub_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm_sub_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        if constexpr( sizeof(T) == 1 )
        {
          self = _mm_sub_epi8(self, other);
        }
        else if constexpr( sizeof(T) == 2 )
        {
          self = _mm_sub_epi16(self, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          self = _mm_sub_epi32(self, other);
        }
        else if constexpr( sizeof(T) == 8 )
        {
          self = _mm_sub_epi64(self, other);
        }
      }
      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub(wide<T, N, avx_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, avx_>, U>)
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      return self_sub(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm256_sub_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm256_sub_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        if constexpr( current_api >= avx2 )
        {
          if constexpr( sizeof(T) == 1 )
          {
            self = _mm256_sub_epi8(self, other);
          }
          else if constexpr( sizeof(T) == 2 )
          {
            self = _mm256_sub_epi16(self, other);
          }
          else if constexpr( sizeof(T) == 4 )
          {
            self = _mm256_sub_epi32(self, other);
          }
          else if constexpr( sizeof(T) == 8 )
          {
            self = _mm256_sub_epi64(self, other);
          }
        }
        else
        {
          auto [s1, s2] = self.slice();
          auto [o1, o2] = other.slice();
          s1 -= o1;
          s2 -= o2;
          self = type {s1, s2};
        }
      }
      return self;
    }
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N, sse_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, sse_>, U>)
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      return self_mul(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::is_same_v<T, double> )
      {
        self = _mm_mul_pd(self, other);
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        self = _mm_mul_ps(self, other);
      }
      else if constexpr( std::is_integral_v<T> )
      {
        if constexpr( sizeof(T) == 2 )
        {
          self = _mm_mullo_epi16(self, other);
        }
        else if constexpr( sizeof(T) == 8 )
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a *= b; }, that, other);
        }
        else if constexpr( sizeof(T) == 4 )
        {
          if constexpr( current_api >= sse4_1 )
          {
            self = _mm_mullo_epi32(self, other);
          }
          else
          {
            using htype  = wide<std::int64_t, fixed<N::value / 2>>;
            htype mhi    = _mm_setr_epi32(0xFFFFFFFFUL, 0x00000000, 0xFFFFFFFFUL, 0x00000000);
            htype mlo    = mhi;
            auto  lself  = _mm_srli_si128(self, 4);
            auto  lother = _mm_srli_si128(other, 4);

            mhi &= htype {_mm_mul_epu32(self, other)};
            mlo &= htype {_mm_mul_epu32(lself, lother)};
            mhi |= htype {_mm_slli_si128(mlo, 4)};
            self = mhi.storage();
          }
        }
        else if constexpr( sizeof(T) == 1 )
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
      }
      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul(wide<T, N, avx_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, avx_>, U>)
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      return self_mul(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm256_mul_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm256_mul_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        constexpr bool require_slice = (sizeof(T) == 1) || (sizeof(T) == 8) || (current_api < avx2);

        if constexpr( require_slice )
        {
          auto that = self;
          self      = aggregate([](auto a, auto b) { return a *= b; }, that, other);
        }
        else
        {
          if constexpr( sizeof(T) == 2 )
          {
            self = _mm256_mullo_epi16(self, other);
          }
          else if constexpr( sizeof(T) == 4 )
          {
            self = _mm256_mullo_epi32(self, other);
          }
        }
      }
    }
    return self;
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N, sse_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, sse_>, U>)
  {
    using type = wide<T, N, sse_>;

    if constexpr( scalar_value<U> )
    {
      return self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm_div_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm_div_ps(self, other);
      }
      else if constexpr( std::integral<T> )
      {
        if constexpr( sizeof(T) == 4 && std::is_signed_v<T> && current_api >= avx )
        {
          auto dividend = _mm256_cvtepi32_pd(self);
          auto divisor  = _mm256_cvtepi32_pd(other);

          self = _mm256_cvttpd_epi32(_mm256_div_pd(dividend, divisor));
        }
        else
        {
          auto that = self;
          self      = map([](auto a, auto b) { return a /= b; }, that, other);
        }
      }

      return self;
    }
  }

  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N, avx_> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N, avx_>, U>)
  {
    using type = wide<T, N, avx_>;

    if constexpr( scalar_value<U> )
    {
      return self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( std::same_as<T, double> )
      {
        self = _mm256_div_pd(self, other);
      }
      else if constexpr( std::same_as<T, float> )
      {
        self = _mm256_div_ps(self, other);
      }
      else
      {
        auto that = self;
        self      = aggregate([](auto a, auto b) { return a /= b; }, that, other);
      }

      return self;
    }
  }
}

#endif
