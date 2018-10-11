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

    template<char... c> constexpr std::uint64_t parse()
    {
      std::uint64_t value = 0;
      char arr[] = {c...};
      for(int i = 0;i<sizeof...(c);++i) value = value*10 + (arr[i] - 48);
      return value;
    }
  }

  namespace literal
  {
    template<char ...c> constexpr auto operator"" _c()
    {
      return detail::idx_<detail::parse<c...>()>{};
    }
  }
} }

#endif
