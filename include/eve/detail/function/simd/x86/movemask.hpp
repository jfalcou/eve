//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>

#include <utility>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N>> const &v ) noexcept
    requires ( !abi_t<T, N>::is_wide_logical ) && x86_abi<abi_t<T, N>>
  {
    return std::pair{v.storage(), eve::lane<1>};
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N>> const &v ) noexcept
    requires ( abi_t<T, N>::is_wide_logical ) && x86_abi<abi_t<T, N>>
  {
    auto raw = [&] {
      if constexpr( std::same_as<abi_t<T, N>, x86_128_> )
      {
              if constexpr( std::is_same_v<T, float > ) return (std::uint16_t)_mm_movemask_ps(v);
        else  if constexpr( std::is_same_v<T, double> ) return (std::uint16_t)_mm_movemask_pd(v);
        else  if constexpr( sizeof(T) == 8 )            return (std::uint16_t)_mm_movemask_pd( _mm_castsi128_pd(v.storage()) );
        else  if constexpr( sizeof(T) == 4 )            return (std::uint16_t)_mm_movemask_ps(_mm_castsi128_ps((v.storage())));
        else                                            return (std::uint16_t)_mm_movemask_epi8(v);
      }
      else
      {
        if constexpr( std::is_same_v<T, float > )     return (std::uint32_t)_mm256_movemask_ps(v);
        else if constexpr( std::is_same_v<T, double>) return (std::uint32_t)_mm256_movemask_pd(v);
        else  if constexpr(sizeof(T) == 8)            return (std::uint32_t)_mm256_movemask_pd(_mm256_castsi256_pd(p.storage()));
        else  if constexpr(sizeof(T) == 4)            return (std::uint32_t)_mm256_movemask_ps(_mm256_castsi256_ps(p.storage()));        else if constexpr( current_api == avx2 )       return (std::uint32_t)_mm256_movemask_epi8(v);
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
