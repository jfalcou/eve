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
  //!
  //! @tparam Substitute Type of the substitute value.
  //! @tparam Target     Type of the target value that will result from the `eve::as_value` call.
  //================================================================================================
  template<typename Substitute, typename Target>
  concept substitute_for = generator_for<Substitute, Target> || std::constructible_from<Target, Substitute>;
  //================================================================================================
  //! @}
  //================================================================================================
}
