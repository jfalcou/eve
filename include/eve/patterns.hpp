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
#include <utility>

namespace eve
{
  //================================================================================================
  // Concept for swizzling pattern
  //================================================================================================
  template<typename T> concept shuffle_pattern = requires(T p)
  {
    { T::size(0)      };
    { T::has_zeros(0) };
    { T::validate(0)  };
  };

  //================================================================================================
  // Basic shuffling/swizzling pattern holder
  //================================================================================================
  template<std::ptrdiff_t... I> struct pattern_
  {
    constexpr std::ptrdiff_t operator()(int i, int) const noexcept
    {
      constexpr std::ptrdiff_t sz = sizeof...(I);
      constexpr std::ptrdiff_t data[] = {I...};

      return i<sz ? data[i] : -1;
    }

    friend std::ostream& operator<<(std::ostream& os, pattern_ const&)
    {
      os << "< ";
      ((os << I<< " "),...);
      return os << ">";
    }

    template<std::ptrdiff_t... O>
    constexpr auto is_similar(pattern_<I..., O...>) const noexcept { return true; }

    template<std::ptrdiff_t... O>
    constexpr auto is_similar(pattern_<O...>) const  noexcept { return false; }

    constexpr bool operator>(int n)  const noexcept { return ((I  > n || I == -1) && ...); }
    constexpr bool operator<(int n)  const noexcept { return ((I  < n || I == -1) && ...); }
    constexpr bool operator>=(int n) const noexcept { return ((I >= n || I == -1) && ...); }
    constexpr bool operator<=(int n) const noexcept { return ((I <= n || I == -1) && ...); }

    constexpr bool operator==(pattern_) const noexcept { return true; }
    constexpr bool operator!=(pattern_) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator==(pattern_<J...>) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator!=(pattern_<J...>) const noexcept { return true; }

    static inline constexpr auto size(int) noexcept { return sizeof...(I); }

    static inline constexpr bool has_zeros(int) noexcept
    {
      return ((I == -1) || ... || false);
    }

    // Ensure that a pattern don't try to reference non-existent lanes
    static constexpr bool validate(int N) noexcept
    {
      return (((I == -1) || (I<N)) && ... && true);
    }
  };

  //================================================================================================
  // basic shuffling/swizzling pattern holder
  //================================================================================================
  template<std::ptrdiff_t... I>
  inline constexpr pattern_<I...> const pattern = {};

  //================================================================================================
  // Turn a lambda into a pattern
  //================================================================================================
  template<typename Generator, int Size = -1>
  struct swizzler_ : Generator
  {
    constexpr swizzler_() noexcept  {}
    using Generator::operator();

    static inline constexpr auto size(int sz) noexcept
    {
      if constexpr(Size==-1) return sz; else return Size;
    }

    static inline constexpr bool has_zeros(int N) noexcept
    {
      for(int i=0;i<N;++i) { if(Generator{}(i,N) == -1) { return true; } }
      return false;
    }

    static constexpr bool validate(int N) noexcept
    {
      auto sz = size(N);
      for(int i=0;i<sz;++i)
        if( (Generator{}(i,sz) >= N) || (Generator{}(i,sz) < -1) )
          return false;
      return true;
    }

    friend std::ostream& operator<<(std::ostream& os, swizzler_ const& s)
    {
      return os << as_pattern<Size>(s);
    }
  };

  template<typename G>
  constexpr swizzler_<G>      swizzler(G) noexcept  { return {}; }

  template<int Size, typename G>
  constexpr swizzler_<G,Size> swizzler(G) noexcept  { return {}; }

  //================================================================================================
  // Convert analytical pattern into value pattern
  //================================================================================================
  template<int N, typename G, int S>
  constexpr auto as_pattern( swizzler_<G,S> const& ) noexcept
  {
    return []<int... I>( std::integer_sequence<int,I...> const&)
    {
      return pattern_< swizzler_<G,S>{}(I,static_cast<int>(sizeof...(I)))... >{};
    }( std::make_integer_sequence<int, swizzler_<G,S>::size(N)>{});
  }

  template<int N, typename T> constexpr auto as_pattern( T const& p ) noexcept
  {
    return p;
  }

  //================================================================================================
  // Markup for 0-ing swizzle index
  //================================================================================================
  inline constexpr int na_ = -1;

  //================================================================================================
  // Zero swizzle : [-1 -1 ... -1]
  //================================================================================================
  template<int N>
  inline constexpr auto zeroing_n = swizzler<N>( [](int, int){ return na_; } );
  inline constexpr auto zeroing   = zeroing_n<-1>;

  //================================================================================================
  // Identity swizzle : [0 1 ... N-1]
  //================================================================================================
  template<int N>
  inline constexpr auto identity_n  = swizzler<N>( [](int i, int){ return i; } );
  inline constexpr auto identity    = identity_n<-1>;

  //-----------------------------------------------------------------------------------------------
  // Broadcast swizzle : [N N ... N]
  template<int V, int N>
  inline constexpr auto broadcast_n = swizzler<N>([](int, int) { return V; });

  template<int V>
  inline constexpr auto broadcast   = broadcast_n<V,-1>;

  //-----------------------------------------------------------------------------------------------
  // Reverse swizzle : [ N-1 ... 2 1 0]
  inline constexpr auto reverse    = swizzler([](int i, int c ) { return c-i-1; });

  //------------------------------------------------------------------------------------------------
  // Slides data left
  template<int O, int S, int N>
  inline constexpr auto slide_left_n  = swizzler<S>( [](int i, int) { return i+O<N ? i+O : na_; } );

  template<int O>
  inline constexpr auto slide_left    = swizzler( [](int i, int c) { return i+O<c ? i+O : na_; } );

  //------------------------------------------------------------------------------------------------
  // Slides data right
  template<int O, int S, int N>
  inline constexpr auto slide_right_n  = swizzler<S>( [](int i, int) { return i<O ? na_ : i-O; } );

  template<int O>
  inline constexpr auto slide_right = swizzler( [](int i, int ) { return i<O ? na_ : i-O; } );

  //------------------------------------------------------------------------------------------------
  // Slides data relative
  template<int O>
  inline constexpr auto slide = swizzler( [](int i, int c)
                                          {
                                            return (O<0)  ? slide_left<-O>(i,c)
                                                          : slide_right<O>(i,c);
                                          }
                                        );

  //----------------------------------------------------------------------------------------------
  // Fix a patternto a given size
  template<int N, shuffle_pattern Pattern >
  constexpr auto fix_pattern(Pattern const& p) noexcept
  {
    return swizzler<N>( p );
  }

  //----------------------------------------------------------------------------------------------
  // Extract a sub-pattern of an existing pattern
  template<int O, int N, shuffle_pattern Pattern >
  constexpr auto pattern_view(Pattern const&) noexcept
  {
    constexpr auto that = swizzler<N>( [](int i, int c) { Pattern q; return q(i+O,c); } );
    return that;
  }

  //----------------------------------------------------------------------------------------------
  // Change the origin of an existing pattern
  template<int O, int N, shuffle_pattern Pattern>
  constexpr auto rebase_pattern(Pattern) noexcept
  {
    constexpr auto that = swizzler<N>(  [](int i, int c)
                                        {
                                          Pattern q;
                                          auto v = q(i+O,c)-O;
                                          return v < -1 ? -1 : v;
                                        }
                                      );
    return that;
  }

  //----------------------------------------------------------------------------------------------
  // Slide the values of an existing pattern
  template<int O, int N, shuffle_pattern Pattern>
  constexpr auto slide_pattern(Pattern) noexcept
  {
    constexpr auto that = swizzler<N> ( [](int i, int c)
                                        {
                                          Pattern q;
                                          auto v = q(i,c)-O;
                                          return v < -1 ? -1 : v;
                                        }
                                      );
    return that;
  }

  //----------------------------------------------------------------------------------------------
  // Modify a patternt to only let 1st or 2nd part fo the shuffle left
  template<bool First, shuffle_pattern Pattern>
  constexpr auto mask_pattern(Pattern) noexcept
  {
    constexpr auto that = swizzler( [](int i, int c)
                                    {
                                      Pattern q;
                                      auto v = q(i,c);
                                      if constexpr(First) return v < c ? v  : -1;
                                      else                return v < c ? -1 :  v - c;
                                    }
                                  );
    return that;
  }
}
