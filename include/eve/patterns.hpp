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

#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  //------------------------------------------------------------------------------------------------
  // type wrapper around lambda patterns
  template<typename F, int Size> struct swizzler_t : F
  {
    constexpr swizzler_t()    noexcept  {}
    constexpr swizzler_t(F f) noexcept : F(f) {}
    using F::operator();

    static inline constexpr auto size(int sz) noexcept
    {
      if constexpr(Size==-1)  return sz;
      else                    return Size;
    }

    inline constexpr bool has_zeros(int N) noexcept
    {
      for(int i=0;i<N;++i)
        if((*this)(i,N) == -1)
          return true;

      return false;
    }
  };

  template<int Size, typename F>
  constexpr swizzler_t<F,Size> swizzler(F f) noexcept { return {f}; }

  template<typename F> constexpr swizzler_t<F,-1> swizzler(F f) noexcept { return {f}; }

  //------------------------------------------------------------------------------------------------
  // Markup for 0-ing swizzle index
  inline constexpr int na_ = -1;

  //------------------------------------------------------------------------------------------------
  // Basic pattern wrapper
  template<int... N>
  inline constexpr auto pattern = swizzler<sizeof...(N)>( [](int i, int)
                                                          {
                                                            int idx[]= {N...};
                                                            constexpr int sz = sizeof...(N);

                                                            return i<sz ? idx[i] : -1;
                                                          }
                                                        );

  //------------------------------------------------------------------------------------------------
  // Identity swizzle : [0 1 ... N-1]
  inline constexpr auto identity = swizzler( [](int i, int){ return i; } );

  //-----------------------------------------------------------------------------------------------
  // Zero swizzle : [-1 -1 ... -1]
  inline constexpr auto zeroing  = swizzler( [](int  , int){ return na_; } );

  //-----------------------------------------------------------------------------------------------
  // Broadcast swizzle : [N N ... N]
  template<int N>
  inline constexpr auto broadcast  = swizzler([](int, int) { return N; });

  //-----------------------------------------------------------------------------------------------
  // Reverse swizzle : [ N-1 ... 2 1 0]
  inline constexpr auto reverse    = swizzler([](int i, int c ) { return c-i-1; });

  //------------------------------------------------------------------------------------------------
  // Slides swizzle: left, right and relative
  template<int O>
  inline constexpr auto slide_left  = swizzler( [](int i, int c) { return i<(c-O) ? i+O : na_; } );

  template<int O>
  inline constexpr auto slide_right = swizzler( [](int i, int ) { return i<O ? na_ : i-O; } );

  template<int O>
  inline constexpr auto slide = swizzler( [](int i, int c)
                                          {
                                            return (O<0)  ? slide_left<-O>(i,c)
                                                          : slide_right<O>(i,c);
                                          }
                                        );

  //----------------------------------------------------------------------------------------------
  // Extract a sub-pattern of an existing pattern
  template<int O, int N, typename P, int S>
  constexpr auto pattern_view(swizzler_t<P,S>) noexcept
  {
    constexpr auto that = swizzler<N>([](int i, int c) { swizzler_t<P,S> q; return q(i+O,c); });
    return that;
  }

  //----------------------------------------------------------------------------------------------
  // Change the origin of an existing pattern
  template<int O, int N, typename P, int S>
  constexpr auto rebase_pattern(swizzler_t<P,S>) noexcept
  {
    constexpr auto that = swizzler<N>(  [](int i, int c)
                                        {
                                          swizzler_t<P,S> q;
                                          auto v = q(i+O,c)-O;
                                          return v < -1 ? -1 : v;
                                        }
                                      );
    return that;
  }

  //----------------------------------------------------------------------------------------------
  // Slide the values of an existing pattern
  template<int O, int N, typename P, int S>
  constexpr auto slide_pattern(swizzler_t<P,S>) noexcept
  {
    constexpr auto that = swizzler<N>([](int i, int c) { swizzler_t<P,S> q; return q(i,c)-O; });
    return that;
  }
}
