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
  //! @addtogroup elliptic
  //! @{
  //! @var ellint_rc
  //!
  //! @brief Callable object computing the degenerate Carlson's elliptic integral
  //!  \f$ \frac12 \int_{0}^{\infty} \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$
  //!
  //! **Required header:** `#include <eve/function/ellint_rc.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rc operation                                    |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x
  //!                 , floating_real_value auto y) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating real values](@ref eve::floating_real_value).
  //!
  //!  This computes the degenerate Carlson's elliptic integral
  //!
  //!  \f[ R_C(x, y) = \frac12 \int_{0}^{\infty} (t+x)^{-1/2}(t+y)^{-1} \mbox{d}t\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  Parameters `x` and `y` must be strictly positive and `y` non zero.
  //!  In any other case the result is nan.
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the Carlson's integral.
  //!
  //! The result type is of the compatibility type of the three parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ellint_rc
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_rc[cond](x, ...)` is equivalent to `if_else(cond,ellint_rc(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ellint_rc.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rc_, ellint_rc);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_rc.hpp>
