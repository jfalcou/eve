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
  //! @var legendre
  //!
  //! @brief Callable object computing the legendre operation.
  //!
  //! **Required header:** `#include <eve/function/legendre.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the legendre operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< integral_value N, floating_value T > auto operator()( N n, T x) const noexcept;
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
  //!Returns [elementwise](@ref glossary_elementwise) the value of the first kind Legendre polynomial of order `n` at `x`.
  //!By choice returns a nan if x is outside of \f$[-1,1]\f$.
  //!
  //!The result type is of the compatibility type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::legendre
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `legendre[cond](x, ...)` is equivalent to `if_else(cond,legendre(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/legendre.hpp>`
  //!
  //!     The expression `diff(legendre)(n,x)` computes the derivative of the function relative to `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/legendre.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(legendre_, legendre);
}

#include <eve/module/real/polynomial/function/regular/generic/legendre.hpp>
