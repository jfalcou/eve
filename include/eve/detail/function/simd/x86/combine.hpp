//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/abi.hpp>
#include <eve/detail/function/simd/x86/make.hpp>
#include <eve/detail/implementation.hpp>


namespace eve::detail
{
  //================================================================================================
  // 2*128-bits regular combine
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(sse2_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    using t_t = wide<T, typename N::combined_type>;
    using s_t = typename t_t::storage_type;

         if constexpr ( has_aggregated_abi_v<t_t>                 )  return s_t {l , h};
    else if constexpr ( native_simd_for_abi<wide<T, N>, x86_256_> )  // 256 -> 512 on avx512
    {
      if constexpr( std::same_as<T, double> )
      {
        auto il = _mm512_castpd_si512(_mm512_castpd256_pd512(l));
        return _mm512_castsi512_pd(_mm512_inserti64x4(il, _mm256_castpd_si256(h), 1));
      }
      else if constexpr( std::same_as<T, float> )
      {
        auto il = _mm512_castps_si512(_mm512_castps256_ps512(l));
        return _mm512_castsi512_ps(_mm512_inserti32x8(il, _mm256_castps_si256(h), 1));
      }
      else
      {
        return _mm512_inserti64x4(_mm512_castsi256_si512(l), h, 1);
      }
    }
    else if constexpr ( native_simd_for_abi<wide<T, N>, x86_128_> )  // 128 -> 256 on avx2
    {
            if constexpr( std::same_as<T, double>) return _mm256_insertf128_pd   (_mm256_castpd128_pd256(l), h, 1);
      else  if constexpr( std::same_as<T, float> ) return _mm256_insertf128_ps   (_mm256_castps128_ps256(l), h, 1);
      else                                         return _mm256_insertf128_si256(_mm256_castsi128_si256(l), h, 1);
    }
    else if constexpr( N() * sizeof(T) == 8 )
    {
            if constexpr( std::same_as<T, double> ) return _mm_shuffle_pd(l, h, 0);
      else  if constexpr( std::same_as<T, float > ) return _mm_shuffle_ps(l, h, 0x44);
      else                                          return _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(l),
                                                                            _mm_castsi128_ps(h),
                                                                            0x44));
    }
    else if constexpr( N() * sizeof(T) == 4 )
    {
      if constexpr( std::same_as<T, float> )
      {
        t_t that = l.storage();
        that.set(1,h.get(0));
        return that.storage();
      }
      else
      {
        auto shuffle_ps = _mm_shuffle_ps(_mm_castsi128_ps(l), _mm_castsi128_ps(h), 0x44);
        return _mm_shuffle_epi32(_mm_castps_si128(shuffle_ps), 0x88);
      }
    }
    //==============================================================================================
    // Handle 1/8th and 1/16th -storage - Those cases are obviously integrals
    //==============================================================================================
    else if constexpr( N()== 2 )
    {
      return make(eve::as<t_t> {}, l.get(0), l.get(1), h.get(0), h.get(1));
    }
    else if constexpr( N() == 1 )
    {
      return make(eve::as<t_t> {}, l.get(0), h.get(0));
    }
  }

  //================================================================================================
  // Non aggregated, skinny logicals
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine ( avx512_ const & , logical<wide<T, N>> const &l
                            , logical<wide<T, N>> const &h
          ) noexcept
      requires x86_abi<abi_t<T, typename N::combined_type>>
  {
    using s_t = typename logical<wide<T, typename N::combined_type>>::storage_type;
    using i_t  = typename s_t::type;
    return s_t{ static_cast<i_t>((h.bitmap().to_ullong() << h.size()) | l.bitmap().to_ullong())};
  }
}
