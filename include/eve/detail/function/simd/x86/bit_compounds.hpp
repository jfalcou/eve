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
  template<scalar_value T, value U, typename N, x86_abi ABI>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, ABI> &self, U const &other) noexcept
  requires((sizeof(wide<T, N, ABI>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      return self &= type{bit_cast(other, as_<T> {})};
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      const     auto bits = bit_cast(other, as_<type> {});
      constexpr auto c    = categorize<type>();
      constexpr bool i    = c && category::integer_;

            if constexpr( c == category::float64x8        ) self = _mm512_and_pd(self, bits);
      else  if constexpr( c == category::float64x4        ) self = _mm256_and_pd(self, bits);
      else  if constexpr( c == category::float64x2        ) self = _mm_and_pd   (self, bits);
      else  if constexpr( c == category::float32x16       ) self = _mm512_and_ps(self, bits);
      else  if constexpr( c == category::float32x8        ) self = _mm256_and_ps(self, bits);
      else  if constexpr( c == category::float32x4        ) self = _mm_and_ps   (self, bits);
      else  if constexpr( i && std::same_as<ABI,x86_512_> ) self = _mm512_and_si512(self, bits);
      else  if constexpr( i && std::same_as<ABI,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_and_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_and_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<ABI,x86_128_> ) self = _mm_and_si128(self, bits);

      return self;
    }
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N, x86_abi ABI>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N, ABI> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, ABI>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bits = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      constexpr auto c = categorize<type>();
      constexpr bool i = c && category::integer_;

            if constexpr  ( c == category::float64x8        ) self = _mm512_or_pd(self, bits);
      else  if constexpr  ( c == category::float64x4        ) self = _mm256_or_pd(self, bits);
      else  if constexpr  ( c == category::float64x2        ) self = _mm_or_pd   (self, bits);
      else  if constexpr  ( c == category::float32x16       ) self = _mm512_or_ps(self, bits);
      else  if constexpr  ( c == category::float32x8        ) self = _mm256_or_ps(self, bits);
      else  if constexpr  ( c == category::float32x4        ) self = _mm_or_ps   (self, bits);
      else  if constexpr  ( i && std::same_as<ABI,x86_512_> ) self = _mm512_or_si512(self, bits);
      else  if constexpr  ( i && std::same_as<ABI,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_or_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_or_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<ABI,x86_128_> ) self = _mm_or_si128(self, bits);

      return self;
    }
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N, x86_abi ABI>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N, ABI> &self, U const &other) noexcept
      requires((sizeof(wide<T, N, ABI>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bits = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<type> {});
      constexpr auto c = categorize<type>();
      constexpr bool i = c && category::integer_;

            if constexpr  ( c == category::float64x8        ) self = _mm512_xor_pd(self, bits);
      else  if constexpr  ( c == category::float64x4        ) self = _mm256_xor_pd(self, bits);
      else  if constexpr  ( c == category::float64x2        ) self = _mm_xor_pd   (self, bits);
      else  if constexpr  ( c == category::float32x16       ) self = _mm512_xor_ps(self, bits);
      else  if constexpr  ( c == category::float32x8        ) self = _mm256_xor_ps(self, bits);
      else  if constexpr  ( c == category::float32x4        ) self = _mm_xor_ps   (self, bits);
      else  if constexpr  ( i && std::same_as<ABI,x86_512_> ) self = _mm512_xor_si512(self, bits);
      else  if constexpr  ( i && std::same_as<ABI,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_xor_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_xor_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<ABI,x86_128_> ) self = _mm_xor_si128(self, bits);

      return self;
    }
  }
}
