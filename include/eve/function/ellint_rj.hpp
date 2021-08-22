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
  //! @var ellint_rj
  //!
  //! @brief Callable object computing the the Carlson's elliptic integral
  //!        \f$\frac32 \int_{0}^{\infty}\scriptstyle(t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\scriptstyle\;\mathrm{d}t\f$
  //!
  //! **Required header:** `#include <eve/function/ellint_rj.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rj operation                                    |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x
  //!                 , floating_real_value auto y
  //!                 , floating_real_value auto z
  //!                 , floating_real_value auto p) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`, `p`:   [floating real values](@ref eve::floating_real_value).
  //!
  //!  This computes the Carlson's elliptic integral
  //!
  //!  \f[ R_J(x, y, z, p) = \frac32 \int_{0}^{\infty} (t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\mbox{d}t\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  Parameters `x`, `y` and  `z` must be non negative at most one of them 0, and `p` non zero.
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
  //!  Higher-order function generating a masked version of eve::ellint_rj
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_rj[cond](x, ...)` is equivalent to `if_else(cond,ellint_rj(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ellint_rj.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rj_, ellint_rj);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_rj.hpp>
