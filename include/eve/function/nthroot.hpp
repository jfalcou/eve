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
  //! @addtogroup exponential
  //! @{
  //! @var nthroot
  //!
  //! @brief Callable object computing the nth root: \f$x^{1/n}\f$.
  //!
  //! **Required header:** `#include <eve/function/nthroot.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the nthroot operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T,integral_value U > auto operator()( T x, U n) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //!`n`:   [integral_value](@ref eve::integral_value). Actually `n` can be a flint.
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of \f$x^{1/n}\f$.
  //!For negative `x` the value returned is a Nan as soon as `n` is not an odd integer.
  //!
  //! The result type is of the compatibility type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::nthroot
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `nthroot[cond](x, ...)` is equivalent to `if_else(cond,nthroot(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::raw
  //!
  //!     **Required header:** `#include <eve/function/diff/nthroot.hpp>`
  //!
  //!     The expression `raw(nthroot)(x,n)` does not care about limiting values and gives less accurate values.
  //!      for instance `nthroot(64.0,3)` is not exactly four but is `3.9999999999999991118` with a 0.5ulp error.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/nthroot.hpp>`
  //!
  //!     The expression `diff_1st(nthroot)(x,n)`
  //!      diff of \f$f\f$, where \f$f\f$ is the function \f$x \rightarrow \ x^{1/n}\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/nthroot.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(nthroot_, nthroot);
}

#include <eve/module/real/math/function/regular/generic/nthroot.hpp>
