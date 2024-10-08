//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/options.hpp>

namespace eve::detail
{
  //================================================================================================
  // Single slice
  //================================================================================================
  template<callable_options O, typename T, typename N, typename Slice>
  EVE_FORCEINLINE wide<T, typename N::split_type>
  slice_(EVE_REQUIRES(sse2_), O const&, wide<T,N> a, Slice) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto s = Slice::value;

    if constexpr( std::same_as<abi_t<T, N>,x86_128_> )
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

          if constexpr( N::value == 2          )  return wide<T, typename N::split_type>{a.get(1)};
          if constexpr( size == abi_t<T, N>::bytes     )  return _mm_shuffle_epi32(a, 0xEE);
          if constexpr( 2 * size == abi_t<T, N>::bytes )  return _mm_shuffle_epi32(a, 0x01);
          else                                    return _mm_shufflelo_epi16(a, 0x01);
        }
      }
    }
    else if constexpr( std::same_as<abi_t<T, N>,x86_256_> )
    {
            if constexpr( std::same_as<T, double> ) return _mm256_extractf128_pd(a, s);
      else  if constexpr( std::same_as<T, float>  ) return _mm256_extractf128_ps(a, s);
      else                                          return _mm256_extractf128_si256(a, s);
    }
    else if constexpr( std::same_as<abi_t<T, N>,x86_512_> )
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
        using retarget_t = typename wide<T, N>::template rebind<std::uint64_t>;
        return bit_cast ( slice( bit_cast(a, as<retarget_t>()),Slice{})
                        , as<wide<T, typename N::split_type>>()
                        );
      }
    }
  }

  template<callable_options O, typename T, typename N, typename Slice>
  EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
  slice_(EVE_REQUIRES(sse2_), O const&, logical<wide<T,N>> a, Slice) noexcept
      requires x86_abi<abi_t<T, N>> && ( !abi_t<T, N>::is_wide_logical )
  {
    using type  = logical<wide<T, typename N::split_type>>;
    using mask  = typename type::storage_type;
    using value = typename mask::type;

    auto v = a.storage().value;

    if constexpr( !Slice::value ) return mask {static_cast<value>(v)};
    else return mask {static_cast<value>(v >> type::size())};
  }

  //================================================================================================
  // Both slice
  //================================================================================================
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(sse2_), O const&, wide<T, N> a) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    std::array<wide<T, typename N::split_type>, 2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(sse2_), O const&, logical<wide<T,N>> a) noexcept
      requires x86_abi<abi_t<T, N>> && (!abi_t<T, N>::is_wide_logical)
  {
    std::array<logical<wide<T, typename N::split_type>>,2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }
}
