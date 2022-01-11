//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/module/real/core/detail/basic_shuffle.hpp>
#include <eve/function/convert.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE wide<T,N> swap_adjacent_groups_( EVE_SUPPORTS(sse2_)
                                                    , wide<T,N> v, fixed<G>
                                                    ) noexcept
  requires(G<=N::value) && x86_abi<abi_t<T, N>>
  {
    constexpr auto sf4 = _MM_SHUFFLE(2, 3, 0, 1);
    using that_t  = wide<T,N>;

    if constexpr(G == N::value)
    {
      return v;
    }
    else
    {
      constexpr auto size = G * sizeof(T);

      if constexpr( std::same_as<abi_t<T, N>,x86_128_> )
      {
        if constexpr( size == 1 )
        {
          if constexpr( current_api >= ssse3 )
          {
            return _mm_shuffle_epi8 ( v.storage()
                                    , _mm_set_epi8(14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1)
                                    );
          }
          else
          {
            auto up = convert(v, as<upgrade_t<T>>{});
            auto r  = swap_adjacent_groups(up,fixed<G>{});

            if constexpr(N::value < 16)
            {
              if constexpr( std::is_signed_v<T> ) return bit_cast(_mm_packs_epi16(r,r), as(v));
              else                                return bit_cast(_mm_packus_epi16(r,r), as(v));
            }
            else
            {
              auto[l,h] = r.slice();
              if constexpr( std::is_signed_v<T> ) return _mm_packs_epi16(l,h);
              else                                return _mm_packus_epi16(l,h);
            }
          }
        }
        else if constexpr( size == 2 )
        {
          auto s =v.storage();
              s = _mm_shufflehi_epi16(s, sf4);
          return  _mm_shufflelo_epi16(s, sf4);
        }
        else if constexpr( size == 4 )
        {
          if constexpr( std::same_as<T,float> ) return _mm_shuffle_ps(v,v, _MM_SHUFFLE(2,3,0,1));
          else
          {
            auto s = v.storage();
            s = _mm_shuffle_epi32(s, sf4);
            return s;
          }
        }
        else if constexpr( size == 8 )
        {
                if constexpr( std::same_as<T,double> )  return _mm_shuffle_pd(v,v,_MM_SHUFFLE2(0,1));
          else  if constexpr( std::same_as<T,float>  )  return _mm_shuffle_ps(v,v, _MM_SHUFFLE(1,0,3,2));
          else
          {
            auto s = v.storage();
            s = _mm_shuffle_epi32(s, _MM_SHUFFLE(1,0,3,2));
            return s;
          }
        }
      }
      else  if constexpr( std::same_as<abi_t<T, N>,x86_256_> )
      {
        if constexpr( size == 1 )
        {
          if constexpr( current_api >= avx2 )
          {
            auto const hm = _mm_set_epi8(14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
            return _mm256_shuffle_epi8(v,_mm256_set_m128i(hm,hm));
          }
          else
          {
            auto[l,h] = v.slice();
            return that_t( swap_adjacent_groups(l,fixed<G>{}), swap_adjacent_groups(h,fixed<G>{}));
          }
        }
        else if constexpr( size == 2 )
        {
          if constexpr( current_api >= avx2 )
          {
              v = _mm256_shufflehi_epi16(v, sf4);
          return  _mm256_shufflelo_epi16(v, sf4);
          }
          else
          {
            auto[l,h] = v.slice();
            return that_t( swap_adjacent_groups(l,fixed<G>{}), swap_adjacent_groups(h,fixed<G>{}));
          }
        }
        else if constexpr( size == 4 )
        {
          if constexpr( std::same_as<T,float>  )
          {
            return _mm256_permutevar_ps(v, as_integer_t<wide<T,N>>(1,0,3,2,5,4,7,6));
          }
          else  if constexpr( current_api >= avx2    )
          {
            return _mm256_shuffle_epi32(v, sf4);
          }
          else
          {
            auto sd = bit_cast(v, as<typename that_t::template rebind<float>>{});
            sd = swap_adjacent_groups(sd, fixed<1>{});
            return bit_cast(sd, as(v));
          }
        }
        else if constexpr( size == 8 )
        {
          if constexpr( std::same_as<T,double> )
          {
            return _mm256_permutevar_pd(v, as_integer_t<wide<T,N>>(2,0,2,0));
          }
          else  if constexpr( std::same_as<T,float> )
          {
            return _mm256_permutevar_ps(v, as_integer_t<wide<T,N>>(6,7,4,5,2,3,0,1));
          }
          else  if constexpr( current_api >= avx2 )
          {
            return _mm256_permute4x64_epi64(v, sf4);
          }
          else
          {
            auto sd = bit_cast(v, as<typename that_t::template rebind<float>>{});
            sd = swap_adjacent_groups(sd, fixed<2>{});
            return bit_cast(sd, as(v));
          }
        }
        else if constexpr( size == 16 )
        {
          if constexpr( std::same_as<T,double> )
          {
            return _mm256_permute2f128_pd(v,v,0x21);
          }
          else  if constexpr( std::same_as<T,float>  )
          {
            auto[l,h] = v.slice();
            return that_t(h,l);
          }
          else  if constexpr( current_api >= avx2    )
          {
            return _mm256_permute4x64_epi64(v, _MM_SHUFFLE(1,0,3,2));
          }
          else
          {
            auto[l,h] = v.slice();
            return that_t(h,l);
          }
        }
      }
      else  if constexpr( std::same_as<abi_t<T, N>,x86_512_> )
      {
        // We have perfect shuffle so LET'S ROCK'N'ROLL
        return basic_shuffle(v, swap_adjacent_groups_pattern<G,N::value> );
      }
    }
  }

  template<real_scalar_value T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE logical<wide<T,N>> swap_adjacent_groups_ ( EVE_SUPPORTS(sse2_)
                                                              , logical<wide<T,N>> v, fixed<G>
                                                              ) noexcept
  requires(G<=N::value) && x86_abi<abi_t<T, N>>
  {
    if constexpr(G == N::value)
    {
      return v;
    }
    else  if constexpr( !abi_t<T, N>::is_wide_logical )
    {
      // Reconstruct mask, swag then turn to mask again
      auto const m = v.mask();
      auto const swag = swap_adjacent_groups(m, fixed<G>{});
      return to_logical(swag);
    }
    else
    {
      // Use the common implementation
      return swap_adjacent_groups_(EVE_RETARGET(cpu_),v, fixed<G>{});
    }
  }
}
