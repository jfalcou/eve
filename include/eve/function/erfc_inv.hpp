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
  //! @addtogroup special
  //! @{
  //! @var erfc_inv
  //!
  //! @brief Callable object computing the inverse of the \f$\mbox{erfc}\f$ function.
  //!
  //! **Required header:** `#include <eve/function/erfc_inv.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the erfc_inv operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](@ref glossary_elementwise) `y` such that `erfc(y)==x`
  //!
  //! The result type is of the same type as the  parameter.
  //! The function returns Nan outside of the interval \f$[0,2]\f$.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::erfc_inv
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `erfc_inv[cond](x, ...)` is equivalent to `if_else(cond,erfc_inv(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/erfc_inv.hpp>`
  //!
  //!     The expression `diff(erfc_inv)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/erfc_inv.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(erfc_inv_, erfc_inv);
}

#include <eve/module/real/special/function/regular/generic/erfc_inv.hpp>
