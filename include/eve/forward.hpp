//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>

namespace eve
{
  template<typename Type> struct logical;

  inline namespace EVE_ABI_NAMESPACE
  {
    // Wrapper for SIMD registers holding arithmetic types with compile-time size
    template<scalar Type, typename Size = expected_cardinal_t<Type>>
    struct wide;
  }
}
