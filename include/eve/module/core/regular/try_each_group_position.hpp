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
  //!    @var try_each_group_position
  //!    @brief
  //!    For a given simd_value and a group size returns a tuple of (x::size() / group_size)
  //!    permuatitions for this register such that each group will be in each position
  //!    exactly once.
  //!
  //!    This is useful when one needs to try each element against something.
  //!    Motivational example could be intersection: try each element from one register
  //!    against another.
  //!    Groups allow you to treat N elements as one.
  //!
  //!    We took the idea for the operation from:
  //!    "Faster-Than-Native Alternatives for x86 VP2INTERSECT Instructions"
  //!    by Guillermo Diez-Canas.
  //!    Link: https://arxiv.org/abs/2112.06342
  //!
  //!   **Parameters**
  //!
  //!     * `x` : [argument](@ref eve::simd_value).
  //!     * `fixed<N>` : number of elements in group
  //!
  //!    **Return value**
  //!
  //!    kumi::tuple of all results
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/try_each_group_position.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(try_each_group_position_, try_each_group_position);
}

#include <eve/module/core/impl/try_each_group_position.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/impl/simd/x86/try_each_group_position.hpp>
#endif
