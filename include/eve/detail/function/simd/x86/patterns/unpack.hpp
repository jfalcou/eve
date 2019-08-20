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
  // Pattern based on UNPACKHI/UNPACKLO and partial zeroing
  //------------------------------------------------------------------------------------------------
  struct unpack_hi
  {
    enum class category { none = -1, full, upper, lower };

    template<typename F, int Size>
    static constexpr auto categorize(swizzler_t<F,Size> const& p,int c)  noexcept
    {
      int p0 = p(0,4), p1 = p(1,4);

      if(c == 2)
      {
              if(p0== 2 && p1== 2) return category::full;
        else  if(p0== 2 && p1==-1) return category::upper;
        else  if(p0==-1 && p1== 2) return category::lower;
        else  return category::none;
      }
      else
      {
        int p2 = p(2,4), p3 = p(3,4);

              if(p0== 2 && p1== 2 && p2== 3 && p3== 3) return category::full;
        else  if(p0== 2 && p1==-1 && p2== 3 && p3==-1) return category::upper;
        else  if(p0==-1 && p1== 2 && p2==-1 && p3== 3) return category::lower;
        else  return category::none;
      }
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      return      (cardinal_v<Wide> <= 4)
              &&  (sizeof(element_type_t<Wide>) == 4)
              && categorize(p,cardinal_v<Wide>) != category::none;
    }
  };

  struct unpack_lo
  {
    enum class category { none = -1, full, upper, lower };

    template<typename F, int Size>
    static constexpr auto categorize(swizzler_t<F,Size> const& p, int c)  noexcept
    {
      int p0 = p(0,4), p1 = p(1,4);

      if(c == 2)
      {
              if(p0== 0 && p1== 0) return category::full;
        else  if(p0== 0 && p1==-1) return category::upper;
        else  if(p0==-1 && p1== 0) return category::lower;
        else  return category::none;
      }
      else
      {
        int p2 = p(2,4), p3 = p(3,4);

              if(p0== 0 && p1== 0 && p2== 1 && p3== 1) return category::full;
        else  if(p0== 0 && p1==-1 && p2== 1 && p3==-1) return category::upper;
        else  if(p0==-1 && p1== 0 && p2==-1 && p3== 1) return category::lower;
        else  return category::none;
      }
    }

    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const& p, as_<Wide> const&)  noexcept
    {
      return      (cardinal_v<Wide> <= 4)
              &&  (sizeof(element_type_t<Wide>) == 4)
              && categorize(p,cardinal_v<Wide>) != category::none;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), unpack_hi const&
                                  , Pattern const&, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;

    auto perm = [&]<typename W>(W r)
    {
      constexpr auto cc = unpack_hi::categorize(Pattern(),Pattern::size(cardinal_v<Wide>));
      if constexpr(cc == unpack_hi::category::full)   return W(_mm_unpackhi_ps(r,r));
      if constexpr(cc == unpack_hi::category::upper)  return W(_mm_unpackhi_ps(r,_mm_setzero_ps()));
      if constexpr(cc == unpack_hi::category::lower)  return W(_mm_unpackhi_ps(_mm_setzero_ps(),r));
    };

    return bit_cast( perm( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )), as_<that_t>() );
  }

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), unpack_lo const&
                                  , Pattern const&, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;

    auto perm = [&]<typename W>(W r)
    {
      constexpr auto cc = unpack_lo::categorize(Pattern(),Pattern::size(cardinal_v<Wide>));
      if constexpr(cc == unpack_lo::category::full)   return W(_mm_unpacklo_ps(r,r));
      if constexpr(cc == unpack_lo::category::upper)  return W(_mm_unpacklo_ps(r,_mm_setzero_ps()));
      if constexpr(cc == unpack_lo::category::lower)  return W(_mm_unpacklo_ps(_mm_setzero_ps(),r));
    };

    return bit_cast( perm( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )), as_<that_t>() );
  }
}
