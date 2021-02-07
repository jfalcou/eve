//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Denis YAROSHEVKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>

#include <utility>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N, ABI>> const &v ) noexcept
    requires ( !ABI::is_wide_logical )
  {
    return std::pair{v.storage(), eve::lane<1>};
  }

  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N, ABI>> const &v ) noexcept
    requires ( ABI::is_wide_logical )
  {
    auto raw = [&] {
      if constexpr( std::same_as<ABI, x86_128_> )
      {
             if constexpr( std::is_same_v<T, float > ) return (std::uint16_t)_mm_movemask_ps(v);
        else if constexpr( std::is_same_v<T, double> ) return (std::uint16_t)_mm_movemask_pd(v);
        else if constexpr( sizeof(T) == 8 )            return (std::uint16_t)_mm_movemask_pd((__m128d)v);
        else if constexpr( sizeof(T) == 4 )            return (std::uint16_t)_mm_movemask_ps((__m128)v);
        else                                           return (std::uint16_t)_mm_movemask_epi8(v);
      }
      else
      {
        if constexpr( std::is_same_v<T, float > )  return (std::uint32_t)_mm256_movemask_ps(v);
        else if constexpr( std::is_same_v<T, double> ) return (std::uint32_t)_mm256_movemask_pd(v);
        else if constexpr( sizeof(T) == 8 )            return (std::uint32_t)_mm256_movemask_pd((__m256d)v);
        else if constexpr( sizeof(T) == 4 )            return (std::uint32_t)_mm256_movemask_ps((__m256)v);
        else if constexpr( current_api == avx2 )       return (std::uint32_t)_mm256_movemask_epi8(v);
        else if constexpr( current_api == avx )
        {
          auto [l, h] = v.slice();
          auto s = h.size();
          if constexpr(sizeof(T) == 2) s *= 2;

          auto top = (std::uint32_t)movemask(h).first;
          auto bottom = movemask(l).first;

          return (top << s) | bottom;
        }
      }
    }();

    return std::pair{raw,  eve::lane<sizeof(T) == 2 ? 2: 1>};
  }

}
