//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CARDINAL_HPP_INCLUDED
#define EVE_CARDINAL_HPP_INCLUDED

#include <eve/forward.hpp>
#include <cstddef>

namespace eve
{
  template<typename Type>
  struct cardinal : std::integral_constant<std::size_t, 1>
  {
  };

  template<typename Type, typename Size, typename ABI>
  struct cardinal<wide<Type, Size, ABI>> : std::integral_constant<std::size_t, Size::value>
  {
  };

  template<typename Type>
  inline constexpr auto cardinal_v = cardinal<Type>::value;

}

#endif
