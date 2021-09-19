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
  //! Swaps the [values](@ref eve::value) `lhs` and `rhs` wherever `mask` evaluates to
  //! `true` or not.
  //!
  //! @params mask      Logical mask to apply over the swap operation.
  //! @params lhs, rhs  Values to swap.
  //!
  //! @groupheader{Example}
  //!
  //! @godbolt{doc/core/swap_if.cpp}
  //!
  //! @}
  //================================================================================================
  template<logical_value Mask, value Value>
  void swap_if(Mask const& mask, Value& lhs, Value& rhs) noexcept
  {
    if constexpr( scalar_value<Mask> )
    {
      using std::swap;
      if( static_cast<bool>(mask) ) swap(lhs,rhs);
    }
    else
    {
      auto tmp  = lhs;
      lhs       = if_else(mask, rhs, lhs);
      rhs       = if_else(mask, tmp  , rhs );
    }
  }

  template<value Value>
  void swap_if(bool mask, Value& lhs, Value& rhs) noexcept
  {
    using std::swap;
    if( static_cast<bool>(mask) ) swap(lhs,rhs);
  }
}
