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
  //================================================================================================
  // Pattern based on shuffle{hi,lo}_epi16 and partial zeroing
  //================================================================================================
  struct shuffle_16
  {
    static constexpr auto none  = 0;
    static constexpr auto low   = 1;
    static constexpr auto high  = 2;
    static constexpr auto both  = 3;

    template<std::ptrdiff_t... I>
    static constexpr auto categorize(pattern_<I...> const& p)  noexcept
    {
            if( p <   4 ) return low;
      else  if( p >=  4 ) return high;
      else                return none;
    }

    template< std::ptrdiff_t I0, std::ptrdiff_t I1, std::ptrdiff_t I2, std::ptrdiff_t I3
            , std::ptrdiff_t I4, std::ptrdiff_t I5, std::ptrdiff_t I6, std::ptrdiff_t I7
            >
    static constexpr auto categorize(pattern_<I0,I1,I2,I3,I4,I5,I6,I7> const&)  noexcept
    {
      constexpr auto l_p  = pattern<I0,I1,I2,I3>;
      constexpr auto h_p  = pattern<I4,I5,I6,I7>;
      constexpr auto l_id = pattern<0,1,2,3>;
      constexpr auto h_id = pattern<4,5,6,7>;

            if( l_p<4     && l_p!=l_id  &&  h_p==h_id             ) return low;
      else  if( l_p==l_id && h_p!=h_id  &&  h_p>=4                ) return high;
      else  if( l_p<4     && l_p!=l_id  &&  h_p!=h_id &&  h_p>=4  ) return both;
      else                                                          return none;
    }

    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> p, as_<In>, as_<Out>)  noexcept
    {
      return  (sizeof(element_type_t<In>) == 2) &&  categorize(p) != none;
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), shuffle_16 const&
                                  , as_<Target> , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto cc = shuffle_16::categorize(Pattern());

    auto perm = [&](auto r)
    {
      if constexpr(cc & shuffle_16::low)
      {
        constexpr auto m = swizzle_mask<Pattern,4>();
        r = _mm_shufflelo_epi16(r, m);
      }

      if constexpr(cc & shuffle_16::high)
      {
        if constexpr (cardinal_v<Target> <= 4)
        {
          constexpr auto m = swizzle_mask<4>(slide_pattern<4,4>(Pattern()));
          r = _mm_shufflelo_epi16( _mm_srli_si128(r,8), m );
        }
        else
        {
          constexpr auto m = swizzle_mask<4>(rebase_pattern<4,4>(Pattern()));
          r = _mm_shufflehi_epi16(r, m );
        }
      }

      return Target(r.storage());
    };

    return process_zeros(perm(v),p);
  }
}
