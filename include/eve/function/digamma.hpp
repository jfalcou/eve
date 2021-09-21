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
  //! @addtogroup special
  //! @{
  //! @var digamma
  //!
  //! @brief Callable object computing logarithmic derivative of the \f$\Gamma\f$ function.
  //!
  //! **Required header:** `#include <eve/function/digamma.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the digamma operation   |
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
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value  the logarithmic derivative
  //!of the \f$\Gamma\f$ function.
  //!
  //! The result type is of the same type as the  parameter.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::digamma
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `digamma[cond](x, ...)` is equivalent to `if_else(cond,digamma(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth<1>
  //!
  //!     **Required header:** `#include <eve/function/diff/digamma.hpp>`
  //!
  //!     The expression `diff(digamma)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/digamma.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(digamma_, digamma);
}

#include <eve/module/real/special/function/regular/generic/digamma.hpp>
