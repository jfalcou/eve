//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/abi.hpp>

namespace eve
{
  template<typename Type>
  struct logical;

  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  template<typename Type,
           typename Size = expected_cardinal_t<Type>,
           typename ABI  = abi_t<Type, Size>>
  struct wide;
}
