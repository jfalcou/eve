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
  // Pattern based on shuffle{hi,lo}_epi16 and partial zeroing
  //------------------------------------------------------------------------------------------------
  struct shuffle_16
  {
    enum class category { none = -1, low = 1, high = 2, both = 3 };

    static constexpr bool is_low(category c) noexcept
    {
      return (static_cast<int>(category::low) & static_cast<int>(c)) != 0;
    }

    static constexpr bool is_high(category c) noexcept
    {
      return (static_cast<int>(category::high) & static_cast<int>(c)) != 0;
    }

    template<typename F, int Size>
    static constexpr auto categorize(swizzler_t<F,Size> const& p, int c)  noexcept
    {
      auto all_lo = [](auto... ps) { return ((ps < 4) && ...); };
      auto all_hi = [](auto... ps) { return ((ps >= 4 || ps == -1) && ...); };

      if(c <= 4)
      {
        // Half short register can only be swizzled as shufflelo_epi16
        int p0 = p(0,4), p1 = p(1,4), p2 = p(2,4), p3 = p(3,4);
        bool lows   = all_lo(p0,p1,p2,p3);
        bool highs  = all_hi(p0,p1,p2,p3);

              if( lows  ) return category::low;
        else  if( highs ) return category::high;
        else              return category::none;
      }
      else
      {
        // Full short register can be swizzled by lo, hi or both.
        int p0 = p(0,8), p1 = p(1,8), p2 = p(2,8), p3 = p(3,8);
        int p4 = p(4,8), p5 = p(5,8), p6 = p(6,8), p7 = p(7,8);

        bool lows     = all_lo(p0,p1,p2,p3);
        bool low_id   = p0==0 && p1==1 && p2==2 && p3==3;
        bool highs    = all_hi(p4,p5,p6,p7);
        bool high_id  = p4==4 && p5==5 && p6==6 && p7==7;

              if( lows    && !low_id  &&  high_id           ) return category::low;
        else  if( low_id  && !high_id &&  highs             ) return category::high;
        else  if( lows    && !low_id  && !high_id &&  highs ) return category::both;
        else                                                  return category::none;
      }
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto sz = swizzler_t<F,Size>::size(cardinal_v<Wide>);
      return      (sz <= 8)
              &&  (sizeof(element_type_t<Wide>) == 2)
              &&  categorize(p,sz) != category::none;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), shuffle_16 const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;
    constexpr auto cc = shuffle_16::categorize(Pattern(),cardinal_v<that_t>);

    auto perm = [&](auto r)
    {
      if constexpr(shuffle_16::is_low(cc))
      {
        constexpr auto m = swizzle_mask<Pattern,4>();
        r = _mm_shufflelo_epi16(r, m);
      }

      if constexpr(shuffle_16::is_high(cc))
      {
        if constexpr (cardinal_v<that_t> <= 4)
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

      return that_t(r.storage());
    };

    return process_zeros(perm(v),p);
  }
}
