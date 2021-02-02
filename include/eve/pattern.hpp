//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <utility>
#include <ostream>

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
  template<std::ptrdiff_t... I> struct pattern_t
  {
    constexpr std::ptrdiff_t operator()(std::ptrdiff_t i, int) const noexcept
    {
      constexpr std::ptrdiff_t sz = sizeof...(I);
      constexpr std::ptrdiff_t data[] = {I...};

      return i<sz ? data[i] : -1;
    }

    friend std::ostream& operator<<(std::ostream& os, pattern_t const&)
    {
      os << "< ";
      ((os << I << " "),...);
      return os << ">";
    }

    template<std::ptrdiff_t... O>
    constexpr auto is_similar(pattern_t<I..., O...>) const noexcept requires(sizeof...(I)>0)
    {
      return true;
    }

    template<std::ptrdiff_t... O>
    constexpr auto is_similar(pattern_t<O...>) const  noexcept { return false; }

    constexpr bool operator>  (std::ptrdiff_t n) const noexcept { return ((I  > n || I == -1) && ...); }
    constexpr bool operator<  (std::ptrdiff_t n) const noexcept { return ((I  < n || I == -1) && ...); }
    constexpr bool operator>= (std::ptrdiff_t n) const noexcept { return ((I >= n || I == -1) && ...); }
    constexpr bool operator<= (std::ptrdiff_t n) const noexcept { return ((I <= n || I == -1) && ...); }

    constexpr bool operator==(pattern_t) const noexcept { return true; }
    constexpr bool operator!=(pattern_t) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator==(pattern_t<J...>) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator!=(pattern_t<J...>) const noexcept { return true; }

    static inline constexpr auto size(int) noexcept { return sizeof...(I); }

    static inline constexpr bool has_zeros(int) noexcept
    {
      return ((I == -1) || ... || false);
    }

    // Ensure that a pattern don't try to reference non-existent lanes
    static constexpr bool validate(std::ptrdiff_t N) noexcept
    {
      return (((I == -1) || (I<N)) && ... && true);
    }
  };

  //================================================================================================
  // basic shuffling/swizzling pattern holder
  //================================================================================================
  template<std::ptrdiff_t... I>
  inline constexpr pattern_t<I...> const pattern = {};

  //================================================================================================
  // Turn a lambda into a pattern
  //================================================================================================
  template<typename Generator, std::ptrdiff_t Size = -1>
  struct swizzler_t : Generator
  {
    constexpr swizzler_t() noexcept  {}
    using Generator::operator();

    static inline constexpr auto size(std::ptrdiff_t sz) noexcept
    {
      if constexpr(Size==-1) return sz; else return Size;
    }

    static inline constexpr bool has_zeros(std::ptrdiff_t N) noexcept
    {
      for(std::ptrdiff_t i=0;i<N;++i) { if(Generator{}(i,N) == -1) { return true; } }
      return false;
    }

    static constexpr bool validate(std::ptrdiff_t N) noexcept
    {
      auto sz = size(N);
      for(std::ptrdiff_t i=0;i<sz;++i)
        if( (Generator{}(i,sz) >= N) || (Generator{}(i,sz) < -1) )
          return false;
      return true;
    }

    friend std::ostream& operator<<(std::ostream& os, swizzler_t const& s)
    {
      return os << as_pattern<Size>(s);
    }
  };

  template<typename G>
  constexpr swizzler_t<G>      swizzle(G) noexcept  { return {}; }

  template<std::ptrdiff_t Size, typename G>
  constexpr swizzler_t<G,Size> swizzle(G) noexcept  { return {}; }

  //================================================================================================
  // Convert analytical pattern into value pattern
  //================================================================================================
  template<std::ptrdiff_t N, typename G, std::ptrdiff_t S>
  constexpr auto as_pattern( swizzler_t<G,S> const& ) noexcept
  {
    return []<int... I>( std::integer_sequence<int,I...> const&)
    {
      return pattern_t< swizzler_t<G,S>{}(I,static_cast<int>(sizeof...(I)))... >{};
    }( std::make_integer_sequence<int, swizzler_t<G,S>::size(N)>{});
  }

  template<std::ptrdiff_t N, typename T> constexpr auto as_pattern( T const& p ) noexcept
  {
    return p;
  }

  //================================================================================================
  // Markup for 0-ing swizzle index
  //================================================================================================
  inline constexpr std::ptrdiff_t na_ = -1;

  //================================================================================================
  // Clamp a pattern to a given size
  //================================================================================================
  template<std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_clamp(Pattern const& p) noexcept
  {
    return swizzle<N>( p );
  }

  //================================================================================================
  // Extract a sub-pattern of an existing pattern
  //================================================================================================
  template<std::ptrdiff_t B, std::ptrdiff_t E, std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_view(Pattern const&) noexcept
  {
    return swizzle<E-B> ( [](auto i, auto) { Pattern q; return q(i+B,N); } );
  }

  //================================================================================================
  // Slide the values of an existing pattern
  //================================================================================================
  template<std::ptrdiff_t O, std::ptrdiff_t N, shuffle_pattern Pattern>
  constexpr auto slide_pattern(Pattern) noexcept
  {
    return swizzle<N>( [](auto i,auto c) { auto v = Pattern{}(i,c)-O; return v < -1 ? -1 : v; } );
  }
}
