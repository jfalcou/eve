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

namespace eve::detail
{
  //================================================================================================
  // Arbitrary SSE2 pattern
  //================================================================================================
  struct sse2_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      using t_t = element_type_t<Out>;
      return (cardinal_v<Out> <= expected_cardinal_t<t_t>::value) && (sizeof(t_t) >= 4 );
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), sse2_match const&
                                  , as_<Target> , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto m  = swizzle_mask<Pattern,sizeof(element_type_t<Wide>)>();

    if constexpr( sizeof(element_type_t<Wide>) == 8 )
    {
      auto perm = [&]<typename W>(W r)
      {
        if constexpr( current_api >= avx) return process_zeros(W(_mm_permute_pd(r  ,m)),p);
        else                              return process_zeros(W(_mm_shuffle_pd(r,r,m)),p);
      };

      return bit_cast( perm( bit_cast(v, as_<wide<double,cardinal_t<Target>>>() )), as_<Target>() );
    }
    else if constexpr( std::same_as<float, element_type_t<Wide>> )
    {
      auto perm = [&](auto r)
      {
        if constexpr( current_api >= avx) return process_zeros(Target(_mm_permute_ps(r  ,m)),p);
        else                              return process_zeros(Target(_mm_shuffle_ps(r,r,m)),p);
      };

      return perm(v);
    }
    else
    {
      return process_zeros(Target(_mm_shuffle_epi32(v,m)),p);
    }
  }
}
