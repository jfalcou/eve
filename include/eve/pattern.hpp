//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <utility>
#include <ostream>
#include <eve/concept/pattern.hpp>

namespace eve
{
  //================================================================================================
  // Index-based pattern holder
  //================================================================================================
  template<std::ptrdiff_t... I> struct pattern_t
  {
    static inline constexpr auto size() noexcept { return sizeof...(I); }

    static inline constexpr bool has_zeros() noexcept
    {
      return ((I == -1) || ... || false);
    }

    // Ensure that a pattern don't try to reference non-existent lanes
    static constexpr bool validate(std::ptrdiff_t N) noexcept
    {
      return (((I == -1) || (I<N)) && ... && true);
    }

    friend std::ostream& operator<<(std::ostream& os, pattern_t const&)
    {
      os << "< ";
      ((os << I << " "),...);
      return os << ">";
    }

    constexpr std::ptrdiff_t operator()(std::ptrdiff_t i, int) const noexcept
    {
      constexpr std::ptrdiff_t sz = sizeof...(I);
      constexpr std::ptrdiff_t data[] = {I...};

      return i<sz ? data[i] : -1;
    }

    constexpr bool strictly_over(std::ptrdiff_t n) const noexcept { return ((I  > n || I == -1) && ...); }
    constexpr bool strictly_under(std::ptrdiff_t n) const noexcept { return ((I  < n || I == -1) && ...); }
    constexpr bool over(std::ptrdiff_t n) const noexcept { return ((I >= n || I == -1) && ...); }
    constexpr bool under(std::ptrdiff_t n) const noexcept { return ((I <= n || I == -1) && ...); }

    constexpr bool operator==(pattern_t) const noexcept { return true; }
    constexpr bool operator!=(pattern_t) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator==(pattern_t<J...>) const noexcept { return false; }

    template<std::ptrdiff_t... J>
    constexpr bool operator!=(pattern_t<J...>) const noexcept { return true; }
  };

  //================================================================================================
  // Index-based pattern variable
  //================================================================================================
  template<std::ptrdiff_t... I> inline constexpr auto pattern = pattern_t<I...>{};

  //================================================================================================
  // Formula-based pattern holder
  //================================================================================================
  template<typename F> struct as_pattern { constexpr as_pattern(F) {} };

  //================================================================================================
  // Converts formula pattern to index pattern
  //================================================================================================
  template<std::ptrdiff_t Sz, typename F> consteval auto fix_pattern(F)
  {
    return []<auto... N>( std::integer_sequence<std::ptrdiff_t,N...> )
    {
      F f;
      return pattern<f(N,Sz)...>;
    }( std::make_integer_sequence<std::ptrdiff_t,Sz>{} );
  }

  template<std::ptrdiff_t Sz, typename F> consteval auto fix_pattern(as_pattern<F>)
  {
    return fix_pattern<Sz>( F{} );
  }

  //================================================================================================
  // Markup for 0-ing swizzle index
  //================================================================================================
  inline constexpr std::ptrdiff_t na_ = -1;

  //================================================================================================
  // Clamp a pattern to a given size
  //================================================================================================
  template<std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_clamp(Pattern const&) noexcept
  {
    return fix_pattern<N>( Pattern{} );
  }

  //================================================================================================
  // Extract a sub-pattern of an existing pattern
  //================================================================================================
  template<std::ptrdiff_t B, std::ptrdiff_t E, std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_view(Pattern const&) noexcept
  {
    return fix_pattern<E-B> ( [](auto i, auto) { Pattern q; return q(i+B,N); } );
  }

  //================================================================================================
  // Slide the values of an existing pattern
  //================================================================================================
  template<std::ptrdiff_t O, std::ptrdiff_t N, shuffle_pattern Pattern>
  constexpr auto slide_pattern(Pattern) noexcept
  {
    return fix_pattern<N> ( [](auto i,auto c)
                            {
                              auto v = Pattern{}(i,c)-O; return v < na_ ? na_ : v;
                            }
                          );
  }
}
