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
  template<typename T, typename Target>
  concept substitute_for = ((arithmetic_value<T> || relaxed_logical_value<T>) && requires { Target{std::declval<T>()}; }) || generator<T>;
  //================================================================================================
  //! @}
  //================================================================================================
}
