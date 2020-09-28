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
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, x86_128_> const &a, Slice const &) noexcept
      requires(N::value > 1)
  {
    using that_t = wide<T, typename N::split_type>;

    if constexpr( !Slice::value )
    {
      return that_t(a.storage());
    }
    else
    {
      if constexpr( std::is_same_v<T, double> )
      {
        return that_t(_mm_shuffle_pd(a, a, 0x01));
      }
      else if constexpr( std::is_same_v<T, float> )
      {
        if constexpr( N::value == 4 )
          return that_t(_mm_shuffle_ps(a, a, 0x0E));
        if constexpr( N::value == 2 )
          return that_t(_mm_shuffle_ps(a, a, 0x11));
      }
      else
      {
        constexpr auto bytes_size = N::value * sizeof(T);

        if constexpr( N::value == 2 )
        {
          return that_t(a[1]);
        }
        if constexpr( bytes_size == eve::x86_128_::bytes )
        {
          return that_t(_mm_shuffle_epi32(a, 0xEE));
        }
        if constexpr( 2 * bytes_size == eve::x86_128_::bytes )
        {
          return that_t(_mm_shuffle_epi32(a, 0x01));
        }
        else
        {
          return that_t(_mm_shufflelo_epi16(a, 0x01));
        }
      }
    }
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, x86_256_> const &a, Slice const &) noexcept
      requires(N::value > 1)
  {
    using that_t = wide<T, typename N::split_type>;

    if constexpr( std::is_same_v<T, double> )
    {
      return that_t(_mm256_extractf128_pd(a, Slice::value));
    }
    else if constexpr( std::is_same_v<T, float> )
    {
      return that_t(_mm256_extractf128_ps(a, Slice::value));
    }
    else
    {
      return that_t(_mm256_extractf128_si256(a, Slice::value));
    }
  }

  //================================================================================================
  // Both slice
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, x86_128_> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
    return that;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, x86_256_> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
    return that;
  }
}

