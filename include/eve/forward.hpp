//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FORWARD_HPP_INCLUDED
#define EVE_FORWARD_HPP_INCLUDED

#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/expected_abi.hpp>

namespace eve
{
  template<typename Type>
  struct logical;

  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  template<typename Type,
           typename Size = expected_cardinal_t<Type>,
           typename ABI  = expected_abi_t<Type, Size>>
  struct wide;
}

#endif
