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
  // Pattern based on MOVHL/MOVLH and partial zeroing
  //------------------------------------------------------------------------------------------------
  struct movlh
  {
    enum class category { none = -1, full, partial };

    template<typename F, int Size>
    static constexpr auto categorize(swizzler_t<F,Size> const& p)  noexcept
    {
      int p0 = p(0,4), p1 = p(1,4), p2 = p(2,4), p3 = p(3,4);

            if(p0== 0 && p1== 1 && p2== 0 && p3== 1) return category::full;
      else  if(p0== 0 && p1== 1 && p2==-1 && p3==-1) return category::partial;
      else  return category::none;
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      return      (cardinal_v<Wide> <= 4)
              &&  categorize(p) != category::none
              &&  sizeof( element_type_t<Wide> ) == 4;
    }
  };

  struct movhl
  {
    enum class category { none = -1, full, partial };

    template<typename F, int Size>
    static constexpr auto categorize(swizzler_t<F,Size> const& p, int c)  noexcept
    {
      int p0 = p(0,4), p1 = p(1,4);

      if(c == 2)
      {
        return (p0== 2 && p1== 3) ? category::full : category::none;
      }
      else
      {
        int p2 = p(2,4), p3 = p(3,4);

              if(p0== 2 && p1== 3 && p2== 2 && p3== 3) return category::full;
        else  if(p0==-1 && p1==-1 && p2== 2 && p3== 3) return category::partial;
        else  return category::none;
      }
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      return      (cardinal_v<Wide> <= 4)
              &&  categorize(p,cardinal_v<Wide>) != category::none
              &&  sizeof( element_type_t<Wide> ) == 4;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), movlh const&
                                  , Pattern const&, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;

    auto perm = [&]<typename W>(W r)
    {
      constexpr auto cc = movlh::categorize(Pattern());
      if constexpr(cc == movlh::category::full)     return W(_mm_movelh_ps(r,r));
      if constexpr(cc == movlh::category::partial)  return W(_mm_movelh_ps(r,_mm_setzero_ps()));
    };

    return bit_cast( perm( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )), as_<that_t>() );
  }

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), movhl const&
                                  , Pattern const&, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;

    auto perm = [&]<typename W>(W r)
    {
      constexpr auto cc = movhl::categorize(Pattern(),Pattern::size(cardinal_v<Wide>));
      if constexpr(cc == movhl::category::full)   return W(_mm_movehl_ps(r,r));
      if constexpr(cc == movhl::category::partial)  return W(_mm_movehl_ps(r,_mm_setzero_ps()));
    };

    return bit_cast( perm( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )), as_<that_t>() );
  }
}
