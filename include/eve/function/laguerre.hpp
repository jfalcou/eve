//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup polynomial
  //! @{
  //! @var laguerre
  //!
  //! @brief Callable object computing the laguerre operation.
  //!
  //! **Required header:** `#include <eve/function/laguerre.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the laguerre operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<integral_value N, floating_value T > auto operator()( N n, T x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [integral valuex](@ref eve::value).
  //!
  //!`x`:   [floating valuex](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the 'physicists' laguerre polynomial of order `n` at `x`:
  //!
  //!The result type is of the compatibility type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::laguerre
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `laguerre[cond](x, ...)` is equivalent to `if_else(cond,laguerre(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/laguerre.hpp>`
  //!
  //!     The expression `diff(laguerre)(n,x)` computes the derivative of the function relative to `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/laguerre.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(laguerre_, laguerre);
}

#include <eve/module/real/polynomial/function/regular/generic/laguerre.hpp>
