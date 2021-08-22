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
  //! @var ellint_rg
  //!
  //! @brief Callable object computing the the Carlson's elliptic integral
  //!        \f$\frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi} \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
  //!                                    +y\sin^2\theta\sin^2\phi
  //!                                    +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$
  //!
  //! **Required header:** `#include <eve/function/ellint_rg.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rg operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_real_value auto  x
  //!                , floating_real_value auto y)
  //!                , floating_real_value auto zconst noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [floating real values](@ref eve::floating_real_value).
  //!
  //!  This computes the Carlson's elliptic integral
  //!
  //! \f[ R_G(x, y, z) = \frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi} \sqrt{x\sin^2\theta\cos^2\phi
  //!                                                                                +y\sin^2\theta\sin^2\phi
  //!                                                                                +z\cos^2\theta} \mbox{d}\theta\mbox{d}\phi\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  Parameters `x` and `y` and `z`must be non-negative.
  //!  In any other case the result is nan.
  //!
  //! **Return value**
  //!
  //!Returns  [elementwise](@ref glossary_elementwise) Carlson's integral.
  //!
  //! The result type is of the compatibility type of the three parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ellint_rg
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_rg[cond](x, ...)` is equivalent to `if_else(cond,ellint_rg(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ellint_rg.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rg_, ellint_rg);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_rg.hpp>
