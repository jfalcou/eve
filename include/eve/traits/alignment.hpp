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

#include <eve/forward.hpp>
#include <cstddef>

namespace eve
{
  template<typename Type>
  struct alignment : std::integral_constant<std::size_t,alignof(Type)>
  {};

  template<typename Type, typename Size, typename ABI>
  struct  alignment<wide<Type, Size, ABI>>
        : std::integral_constant<std::size_t,wide<Type, Size, ABI>::static_alignment>
  {};

  template<typename Type>
  struct alignment<logical<Type>> : alignment<Type>
  {
  };

  template<typename Type>
  using alignment_t = typename alignment<Type>::type;

  template<typename Type>
  inline constexpr auto alignment_v = alignment<Type>::value;
}
