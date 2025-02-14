//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <concepts>
#include <eve/concept/value.hpp>
#include <eve/concept/generator.hpp>

namespace eve
{
  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept substitute_for
  //! @brief Specify that a type can be used as a substitute for another type after calling
  //!        `eve::as_value` on a value of the first type.
  //================================================================================================
  template<typename S, typename Target>
  concept substitute_for = generator_for<S, Target> || ((arithmetic_value<S> || relaxed_logical_value<S>) && requires(S s) { Target{s}; });
  //================================================================================================
  //! @}
  //================================================================================================
}
