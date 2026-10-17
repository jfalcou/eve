//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi.hpp>
#include <eve/arch/expected_width.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>

namespace eve
{
  template<typename Type> struct logical;

  inline namespace EVE_ABI_NAMESPACE
  {
    // Wrapper for SIMD registers holding arithmetic types with compile-time size
    template<arithmetic_scalar_value Type, width_type Width = expected_width_v<Type>>
    requires (is_valid_width<Width>)
    struct wide;
  }
}
