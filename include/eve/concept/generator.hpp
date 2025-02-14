//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/invocable.hpp>
#include <eve/detail/kumi.hpp>

#include <type_traits>

namespace eve
{
  //====================================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept generator
  //! The concept `generator<Constant>` is satisfied if `Constant` is built as a eve::constant_callable.
  //!
  //! @tparam G Type of the generator to check.
  //!
  //! @groupheader{Examples}
  //!   - `eve::one_t`
  //====================================================================================================================
  template<typename Constant>
  concept generator = requires { typename Constant::constant_callable_tag; };
  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept generator_from
  //! The concept `generator_for` is satisfied if `G` satisfies eve::generator and can be called with a
  //! `eve::as<T>` argument.
  //!
  //! @tparam G Type of the generator to check.
  //! @tparam T Type of the argument to pass to the generator.
  //!
  //! @groupheader{Examples}
  //!   - `eve::one_t` satisfies `generator_for<int>`
  //!   - `eve::nbmantissabits_t` satisfies `generator_for<float>` but not `generator_for<int>`
  //====================================================================================================================
  template<typename G, typename T>
  concept generator_for = generator<G> && requires(G g, as<T> t) { g(t); };
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
