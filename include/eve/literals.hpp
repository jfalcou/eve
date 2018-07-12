//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_LITERALS_HPP_INCLUDED
#define EVE_LITERALS_HPP_INCLUDED

#include <type_traits>
#include <cstddef>

namespace eve
{
  namespace detail
  {
    template<std::uint64_t N> using idx_ = std::integral_constant<std::uint64_t,N>;

    constexpr int to_int(char c) { return static_cast<int>(c) - 48; }

    template< std::size_t N> constexpr std::uint64_t parse(int, const char (&)[N], idx_<0> const&)
    {
      return 0;
    }

    template< std::size_t N, std::size_t I>
    constexpr std::uint64_t parse(int base, const char (&arr)[N], idx_<I> const&)
    {
      return to_int(arr[I - 1]) * base + parse<N>(base*10, arr,idx_<I-1>{});
    }

    // Intermediate trampoline so MSVC doesn't cry
    template<std::size_t N,char... c> constexpr std::uint64_t parse(int base)
    {
      return parse<N>(base, {c...}, idx_<N>{});
    }
  }

  namespace literal
  {
    template <char ...c>
    constexpr idx_< eve::detail::parse<sizeof...(c),c...>(1)> operator"" _c()
    {
      return {};
    }
  }
} }

#endif
