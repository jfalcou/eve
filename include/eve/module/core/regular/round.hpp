//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup rounding
  //! @{
  //! @var round
  //!
  //! @brief Callable object computing the round operation.
  //!
  //! **Required header:** `#include <eve/function/round.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the round operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  [elementwise](@ref glossary_elementwise) the integer nearest to `x`.
  //!
  //!If `x` is an exact half-integer the rouding is made to the nearest even integer.
  //!
  //!The call to `round(a)` is equivalent to the call `nearest(a)`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::round
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `round[cond](x, ...)` is equivalent to `if_else(cond,round(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::downward
  //!
  //!     The expression `downward(round)(x)` is equivalent to `floor(x)`.
  //!
  //!  * eve::upward
  //!
  //!     The expression `upward(round)(x)` is equivalent to `ceil(x)`.
  //!
  //!  * eve::to_nearest
  //!
  //!     The expression `to_nearest(round)(x)` is equivalent to `nearest(x)`.
  //!
  //!  * eve::toward_zero
  //!
  //!     The expression `toward_zero(round)(x)` is equivalent to `trunc(x)`.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/round.hpp>`
  //!
  //!     The expression `diff(round)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/round.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(round_, round);
}

#include <eve/module/arithmetic/regular/impl/round.hpp>
