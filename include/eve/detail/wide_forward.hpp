//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi.hpp>
#include <eve/traits/width.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/traits/width.hpp>

EVE_NAMESPACE
{
  template<typename Type> struct logical;

  template<arithmetic_scalar_value Type, width_type Width = expected_width_v<Type>>
  requires (is_valid_width<Width>)
  struct wide;
}
