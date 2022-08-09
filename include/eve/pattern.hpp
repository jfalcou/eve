//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/pattern.hpp>
#include <utility>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief Shuffling pattern
  //!
  //! Holds the index describing a compile-time shuffling pattern.
  //!
  //! @tparam I  Index of the shuffling pattern
  //================================================================================================
  template<std::ptrdiff_t... I> struct pattern_t
  {
    //! Size of the pattern in number of indices
    static inline constexpr auto size() noexcept { return sizeof...(I); }

    //! Checks if a pattern contains any zeroing index
    static inline constexpr bool has_zeros() noexcept
    {
      return ((I == -1) || ... || false);
    }

    //! Ensure that a pattern don't try to reference non-existent lanes
    static constexpr bool validate(std::ptrdiff_t N) noexcept
    {
      return (((I == -1) || (I<N)) && ... && true);
    }

    //! Stream insertion operator for shuffling pattern
    friend std::ostream& operator<<(std::ostream& os, pattern_t const&)
    {
      os << "< ";
      ((os << I << " "),...);
      return os << ">";
    }

    //! Returns the index to use for accessing the `i`th element of a shuffled eve::wide
    constexpr std::ptrdiff_t operator()(std::ptrdiff_t i, int) const noexcept
    {
      constexpr std::ptrdiff_t sz = sizeof...(I);
      constexpr std::ptrdiff_t data[] = {I...};

      return i<sz ? data[i] : -1;
    }

    //! Checks if all non zeroing-indexes in a pattern are greater than a given index
    constexpr bool strictly_over(std::ptrdiff_t n) const noexcept { return ((I  > n || I == -1) && ...); }

    //! Checks if all non zeroing-indexes in a pattern are leser than a given index
    constexpr bool strictly_under(std::ptrdiff_t n) const noexcept { return ((I  < n || I == -1) && ...); }

    //! Checks if all non zeroing-indexes in a pattern are strictly greater or equal than a given index
    constexpr bool over(std::ptrdiff_t n) const noexcept { return ((I >= n || I == -1) && ...); }

    //! Checks if all non zeroing-indexes in a pattern are strictly lesser or equal than a given index
    constexpr bool under(std::ptrdiff_t n) const noexcept { return ((I <= n || I == -1) && ...); }

    //! Checks equality with another pattern
    template<std::ptrdiff_t... J>
    constexpr bool operator==(pattern_t<J...>) const noexcept { return false; }
    constexpr bool operator==(pattern_t) const noexcept { return true; }

    //! Checks inequality with another pattern
    template<std::ptrdiff_t... J>
    constexpr bool operator!=(pattern_t<J...>) const noexcept { return true; }
    constexpr bool operator!=(pattern_t) const noexcept { return false; }
  };

  //! @brief Tag for zeroing swizzle index
  inline constexpr std::ptrdiff_t na_ = -1;

  //! @brief Generate a shuffling pattern
  template<std::ptrdiff_t... I> inline constexpr auto pattern = pattern_t<I...>{};

  //================================================================================================
  //! @}
  //================================================================================================

  //! @relates eve::pattern_t
  //! @brief Formula-based pattern holder
  template<typename F> struct as_pattern { constexpr as_pattern(F) {} };

  //! @relates eve::pattern_t
  //! @brief Converts a formula pattern to index pattern
  template<std::ptrdiff_t Sz, typename F> constexpr auto fix_pattern(F)
  {
    return []<auto... N>( std::integer_sequence<std::ptrdiff_t,N...> )
    {
      return pattern<F{}(N,Sz)...>;
    }( std::make_integer_sequence<std::ptrdiff_t,Sz>{} );
  }

  template<std::ptrdiff_t Sz, typename F> constexpr auto fix_pattern(as_pattern<F>)
  {
    return fix_pattern<Sz>( F{} );
  }

  //! @relates eve::pattern_t
  //! @brief Clamp a pattern to a given size
  template<std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_clamp(Pattern const&) noexcept
  {
    return fix_pattern<N>( Pattern{} );
  }

  //================================================================================================
  //! @relates eve::pattern_t
  //! @brief Extract a sub-pattern of an existing pattern
  //!
  //! Constructs a pattern by extracting all index from a pattern of size `N` between `B` and `E`.
  //!
  //! @tparam B Position of first index to extract
  //! @tparam E Position of last index to extract
  //! @tparam N Size of the pattern to extract from
  //!
  //!
  //================================================================================================
  template<std::ptrdiff_t B, std::ptrdiff_t E, std::ptrdiff_t N, shuffle_pattern Pattern >
  constexpr auto pattern_view(Pattern const&) noexcept
  {
    return fix_pattern<E-B> ( [](auto i, auto) { Pattern q; return q(i+B,N); } );
  }

  //! @relates eve::pattern_t
  //! Slide the values of an existing pattern
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
