//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_floating_point.hpp>

namespace eve::detail
{
  //================================================================================================
  // Converting from aggregation of x86_128 to x86_128
  //================================================================================================
  template<real_scalar_value In, typename N, real_scalar_value Out>
  requires( std::same_as<typename wide<Out,N>::abi_type, x86_128_>)
  EVE_FORCEINLINE wide<Out,N>
  convert_(EVE_SUPPORTS(sse2_), wide<In, N, aggregated_> const &v0, as_<Out> const &tgt) noexcept
  {
    // shortx16 -> charx16 is the only case we care about
    if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) )
    {
      auto[l,h] = v0.slice();
      l &= static_cast<In>(0x00FFU);
      h &= static_cast<In>(0x00FFU);

      return _mm_packus_epi16(l,h);
    }
    else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) )
    {
      if constexpr(sizeof(Out) == 2)
      {
        auto[l,h] = v0.slice();

        if constexpr( current_api >= sse4_1 )
        {
          l &= static_cast<In>(0x0000FFFFU);
          h &= static_cast<In>(0x0000FFFFU);

          return _mm_packus_epi32(l,h);
        }
        else if constexpr( current_api >= ssse3 )
        {
          auto l16 = bit_cast(l, as_<wide<Out>>());
          auto h16 = bit_cast(h, as_<wide<Out>>());

          return l16[pattern<0,2,4,6,-1,-1,-1,-1>] | h16[pattern<-1,-1,-1,-1,0,2,4,6>];
        }
        else
        {
          l = _mm_shufflehi_epi16(l, _MM_SHUFFLE(2,0,2,0));
          l = _mm_shufflelo_epi16(l, _MM_SHUFFLE(2,0,2,0));
          l = _mm_shuffle_epi32  (l, _MM_SHUFFLE(2,0,2,0));

          h = _mm_shufflehi_epi16(h, _MM_SHUFFLE(2,0,2,0));
          h = _mm_shufflelo_epi16(h, _MM_SHUFFLE(2,0,2,0));
          h = _mm_shuffle_epi32  (h, _MM_SHUFFLE(2,0,2,0));

          return bit_cast( _mm_shuffle_ps ( bit_cast(l, as_<as_floating_point_t<decltype(l)>>())
                                          , bit_cast(h, as_<as_floating_point_t<decltype(h)>>())
                                          , _MM_SHUFFLE(1,0,1,0)
                                          )
                                , as_<wide<Out>>()
                                );
        }
      }
      else
      {
        return convert(convert(v0, as_<downgrade_t<In>>()), as_<Out>());
      }
    }
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }
}
