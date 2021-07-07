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
  //! @addtogroup hyperbolic
  //! @{
  //! @var acosh
  //!
  //! @brief Callable object performing the computation of acosh.
  //!
  //! **Required header:** `#include <eve/function/acosh.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acosh   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#elment-wise) inverse hyperbolic cosine of the input.
  //!For values in the domain `x>1`, the inverse hyperbolic cosine is semantically equivalent to \f$\log(x+\sqrt{x^2-1})\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is less than \f$1\f$ or `Nan`, `NaN` is returned.
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element is \f$+\infty\f$, \f$+\infty\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::acosh
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `acosh[cond](x, ...)` is equivalent to `if_else(cond,acosh(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/acosh.hpp>
  //! 
  //!  
  //!     The expression `diff(acosh)(x)` computes the derivative of the function at `x`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/acosh.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(acosh_, acosh);
}

#include <eve/module/real/math/function/regular/generic/acosh.hpp>
