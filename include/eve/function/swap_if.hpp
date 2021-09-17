//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @brief Conditional swap
  //!
  //! **Required header:** `#include <eve/function/swap_if.hpp>`
  //!
  //! Swaps the [SIMD values](@ref eve::simd_value) `lhs` and `rhs` wherever `mask` evaluates to
  //! `true`.
  //!
  //! @params mask      Mask to apply over the swap operation.
  //! @params lhs, rhs  Values to swap.
  //!
  //! @groupheader{Example}
  //!
  //! @godbolt{doc/core/swap_if.cpp}
  //!
  //! @}
  //================================================================================================
  template<logical_value Mask, simd_value Value>
  void swap_if(Mask const& mask, Value& lhs, Value& rhs) noexcept
  {
    auto tmp  = lhs;
    lhs       = if_else(mask, rhs, lhs);
    rhs       = if_else(mask, tmp  , rhs );
  }
}
