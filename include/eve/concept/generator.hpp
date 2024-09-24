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
  //! @concept generator
  //! The concept `generator<Constant>` is satisfied if `Constant` is built as a eve::constant_callable.
  //!
  //! @groupheader{Examples}
  //!   - `eve::one`
  //====================================================================================================================
  template<typename Constant>
  concept generator = requires { typename Constant::constant_callable_tag; };
}
