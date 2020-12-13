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

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

#include <cstddef>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // Single slice
  //================================================================================================
  template<typename T, typename N, x86_abi ABI, typename Slice>
  EVE_FORCEINLINE wide<T, typename N::split_type>
  slice(sse2_ const&, wide<T,N,ABI> const &a, Slice const &) noexcept requires(N::value > 1)
  {
    constexpr auto s = Slice::value;

    if constexpr( std::same_as<ABI,x86_128_> )
    {
      if constexpr( !s )
      {
        return a.storage();
      }
      else
      {
              if constexpr( std::same_as<T, double> ) return _mm_shuffle_pd(a, a, 0x01);
        else  if constexpr( std::same_as<T, float> )
        {
          if constexpr( N::value == 4 ) return _mm_shuffle_ps(a, a, 0x0E);
          if constexpr( N::value == 2 ) return _mm_shuffle_ps(a, a, 0x11);
        }
        else
        {
          constexpr auto size = N::value * sizeof(T);

          if constexpr( N::value == 2          )  return wide<T, typename N::split_type>{a[1]};
          if constexpr( size == ABI::bytes     )  return _mm_shuffle_epi32(a, 0xEE);
          if constexpr( 2 * size == ABI::bytes )  return _mm_shuffle_epi32(a, 0x01);
          else                                    return _mm_shufflelo_epi16(a, 0x01);
        }
      }
    }
    else if constexpr( std::same_as<ABI,x86_256_> )
    {
            if constexpr( std::same_as<T, double> ) return _mm256_extractf128_pd(a, s);
      else  if constexpr( std::same_as<T, float>  ) return _mm256_extractf128_ps(a, s);
      else                                          return _mm256_extractf128_si256(a, s);
    }
    else if constexpr( std::same_as<ABI,x86_512_> )
    {
            if constexpr( std::same_as<T, double> )         return _mm512_extractf64x4_pd(a, s);
      else  if constexpr( std::integral<T> && sizeof(T)==8) return _mm512_extracti64x4_epi64(a, s);
      else  if constexpr( spy::supports::avx512::dq_ )
      {
        if constexpr( std::same_as<T, float> )  return _mm512_extractf32x8_ps(a, s);
        else                                    return _mm512_extracti32x8_epi32(a, s);
      }
      else
      {
        // Slice bits via uint64 then go back
        using retarget_t = typename wide<T, N, avx512_>::template rebind<std::uint64_t>;
        return bit_cast ( slice( bit_cast(a, as<retarget_t>()),Slice{})
                        , as<wide<T, typename N::split_type>>()
                        );
      }
    }
  }

  template<typename T, typename N, x86_abi ABI, typename Slice>
  EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
  slice(sse2_ const&, logical<wide<T,N,ABI>> const &a, Slice const &) noexcept requires(N::value > 1)
  {
    if constexpr( !ABI::regular_logical_register )
    {
      using type  = logical<wide<T, typename N::split_type>>;
      using mask  = typename type::storage_type;
      using value = typename mask::type;

      auto v = a.storage().value;

      if constexpr( !Slice::value ) return mask{static_cast<value>(v)};
      else                          return mask{static_cast<value>(v >> type::static_size)};
    }
    else
    {
      return slice(cpu_{}, a, Slice{});
    }
  }

  //================================================================================================
  // Both slice
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto slice(sse2_ const&, wide<T, N, ABI> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that { slice(sse2_{}, a, lower_)
                                                        , slice(sse2_{}, a, upper_)
                                                        };
    return that;
  }

  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto slice(sse2_ const&, logical<wide<T,N,ABI>> const &a) noexcept
  requires(N::value > 1)
  {
    std::array<logical<wide<T, typename N::split_type>>, 2> that{ slice(sse2_{}, a, lower_)
                                                                , slice(sse2_{}, a, upper_)
                                                                };
    return that;
  }
}
