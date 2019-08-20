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

#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Arbitrary SSE2 pattern
  // Deals with 32-64 bits values only
  //------------------------------------------------------------------------------------------------
  struct any_sse2
  {
    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const&, as_<Wide> const&)  noexcept
    {
      using t_t = element_type_t<Wide>;
      return (cardinal_v<Wide> <= expected_cardinal_t<t_t>::value) && (sizeof(t_t) >= 4 );
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), any_sse2 const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    constexpr auto m  = swizzle_mask<Pattern,sizeof(element_type_t<Wide>)>();
    using that_t      = as_wide_t<Wide,fixed<sz>>;

    if constexpr( sizeof(element_type_t<Wide>) == 8 )
    {
      auto perm = [&]<typename W64>(W64 r)
      {
        if constexpr( current_api >= avx) return process_zeros(W64(_mm_permute_pd(r  ,m)),p);
        else                              return process_zeros(W64(_mm_shuffle_pd(r,r,m)),p);
      };

      return bit_cast( perm( bit_cast(v, as_<wide<double,cardinal_t<Wide>>>() )), as_<that_t>() );
    }
    else if constexpr( std::same_as<float, element_type_t<Wide>> )
    {
      auto perm = [&](auto r)
      {
        if constexpr( current_api >= avx) return process_zeros(that_t(_mm_permute_ps(r  ,m)),p);
        else                              return process_zeros(that_t(_mm_shuffle_ps(r,r,m)),p);
      };

      return perm(v);
    }
    else
    {
      return process_zeros(that_t(_mm_shuffle_epi32(v,m)),p);
    }
  }
}
