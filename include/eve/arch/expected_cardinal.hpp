//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_EXPECTED_CARDINAL_PACK_HPP_INCLUDED
#define EVE_ARCH_EXPECTED_CARDINAL_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/limits.hpp>
#include <array>

namespace eve
{
  template<typename Type, typename API = EVE_CURRENT_API>
  struct  expected_cardinal
        : std::integral_constant< std::size_t
                                , limits<API>::template expected_cardinal<Type>
                                >
  {};

  template<typename Type, typename API = EVE_CURRENT_API>
  using expected_cardinal_t = typename expected_cardinal<Type,API>::type;

  template<typename Type, typename API = EVE_CURRENT_API>
  constexpr inline auto expected_cardinal_v = expected_cardinal<Type,API>::value;
}

#endif
