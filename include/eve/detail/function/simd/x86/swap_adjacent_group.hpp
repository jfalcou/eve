//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/function/convert.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI, std::ptrdiff_t G>
  EVE_FORCEINLINE wide<T,N,ABI> swap_adjacent_group_( EVE_SUPPORTS(cpu_)
                                                    , wide<T,N,ABI> v, fixed<G>
                                                    ) noexcept
  requires(G<=N::value)
  {
    using sf4     = std::integral_constant<int,_MM_SHUFFLE(2, 3, 0, 1)>;
    using that_t  = wide<T,N,ABI>;

    if constexpr(G == N::value)
    {
      return v;
    }
    else
    {
      constexpr auto size = G * sizeof(T);

      if constexpr( std::same_as<ABI,x86_128_> )
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
            auto up = convert(v, as_<upgrade_t<T>>{});
            auto r  = swap_adjacent_group(up,fixed<G>{});
            auto[l,h] = r.slice();
            return _mm_packs_epi16(l,h);
          }
        }
        else if constexpr( size == 2 )
        {
          auto s =v.storage();
              s = _mm_shufflehi_epi16(s, sf4::value);
          return  _mm_shufflelo_epi16(s, sf4::value);
        }
        else if constexpr( size == 4 )
        {
          if constexpr( std::same_as<T,float> ) return v[pattern<1,0,3,2>];
          else
          {
            auto s = v.storage();
            s = _mm_shuffle_epi32(s, sf4::value);
            return s;
          }
        }
        else if constexpr( size == 8 )
        {
                if constexpr( std::same_as<T,double> )  return v[pattern<1,0>];
          else  if constexpr( std::same_as<T,float>  )  return v[pattern<2,3,0,1>];
          else
          {
            auto s = v.storage();
            s = _mm_shuffle_epi32(s, _MM_SHUFFLE(1,0,3,2));
            return s;
          }
        }
      }
      else  if constexpr( std::same_as<ABI,x86_256_> )
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
            return that_t( swap_adjacent_group(l,fixed<G>{}), swap_adjacent_group(h,fixed<G>{}));
          }
        }
        else if constexpr( size == 2 )
        {
          if constexpr( current_api >= avx2 )
          {
              v = _mm256_shufflehi_epi16(v, sf4::value);
          return  _mm256_shufflelo_epi16(v, sf4::value);
          }
          else
          {
            auto[l,h] = v.slice();
            return that_t( swap_adjacent_group(l,fixed<G>{}), swap_adjacent_group(h,fixed<G>{}));
          }
        }
        else if constexpr( size == 4 )
        {
          if constexpr( std::same_as<T,float>  )  return v[pattern<1,0,3,2,5,4,7,6>];
          else  if constexpr( current_api >= avx2    )
          {
            return _mm256_shuffle_epi32(v, sf4::value);
          }
          else
          {
            auto sd = bit_cast(v, as_<typename that_t::template rebind<float>>{});
            sd = swap_adjacent_group(sd, fixed<1>{});
            return bit_cast(sd, as(v));
          }
        }
        else if constexpr( size == 8 )
        {
                if constexpr( std::same_as<T,double> )  return v[pattern<1,0,2,3>];
          else  if constexpr( std::same_as<T,float>  )  return v[pattern<2,3,0,1,6,7,4,5>];
          else  if constexpr( current_api >= avx2    )
          {
            return _mm256_permute4x64_epi64(v, sf4::value);
          }
          else
          {
            auto sd = bit_cast(v, as_<typename that_t::template rebind<float>>{});
            sd = swap_adjacent_group(sd, fixed<2>{});
            return bit_cast(sd, as(v));
          }
        }
        else if constexpr( size == 16 )
        {
                if constexpr( std::same_as<T,double> )  return v[pattern<2,3,0,1>];
          else  if constexpr( std::same_as<T,float>  )  return v[pattern<4,5,6,7,0,1,2,3>];
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
      else  if constexpr( std::same_as<ABI,x86_512_> )
      {
        // We have perfect swizzle so LET'S ROCK'N'ROLL
        return basic_swizzle(v, swap_adjacent_group_n<G,N::value> );
      }
    }
  }

  template<real_scalar_value T, typename N, x86_abi ABI, std::ptrdiff_t G>
  EVE_FORCEINLINE logical<wide<T,N,ABI>> swap_adjacent_group_ ( EVE_SUPPORTS(cpu_)
                                                              , logical<wide<T,N,ABI>> v, fixed<G>
                                                              ) noexcept
  requires(G<=N::value)
  {
    if constexpr(G == N::value)
    {
      return v;
    }
    else  if constexpr( !ABI::is_wide_logical )
    {
      // Reconstruct mask, swag then turn to mask again
      auto const m = v.mask();
      auto const swag = swap_adjacent_group(m, fixed<G>{});
      return to_logical(swag);
    }
    else
    {
      // Use cpu basic implementation via bit_cast & mask()
      return swap_adjacent_group_(EVE_RETARGET(cpu_),v, fixed<G>{});
    }
  }
}
