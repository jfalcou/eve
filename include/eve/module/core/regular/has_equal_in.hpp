//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //!    @var has_equal_in
  //!
  //!    @brief
  //!    Given two simd_values: `x`, `match_against` returns a logical mask.
  //!    The res[i] == eve::any(x[i] == match_against);
  //!
  //!    Optional last parameter allows to ovewrite the equality from `eve::is_equal`
  //!    to an arbitrary simd binary predicate.
  //!
  //!    We took the idea for the operation from:
  //!    "Faster-Than-Native Alternatives for x86 VP2INTERSECT Instructions"
  //!    by Guillermo Diez-Canas.
  //!    Link: https://arxiv.org/abs/2112.06342
  //!
  //!   **Parameters**
  //!     * `x` : [argument](@ref eve::simd_value).
  //!     * `match_against` [argument](@ref eve::simd_value).
  //!     * `predicate` (default `eve::is_equal_to`)
  //!
  //!   **Return value**
  //!
  //!   logical built as described previously
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/has_equal_in.cpp}
  //!
  //================================================================================================
  EVE_MAKE_CALLABLE(has_equal_in_, has_equal_in);
}

#include <eve/module/core/regular/impl/has_equal_in.hpp>
