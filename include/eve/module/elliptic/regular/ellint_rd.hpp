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
  //! @var ellint_rd
  //!
  //! @brief Callable object computing the  the Carlson's elliptic integral
  //!         \f$ \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2} (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
  //!
  //! **Required header:** #include <eve/module/elliptic.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rd operation                                    |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x
  //!                 , floating_real_value auto y
  //!                 , floating_real_value auto z) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [floating real values](@ref eve::floating_real_value).
  //!
  //!  This computes the Carlson's elliptic integral
  //!
  //!  \f[ R_D(x, y, z) = \frac32 \int_{0}^{\infty} [(t+x)(t+y)]^{-1/2} (t+z)^{-3/2} \mbox{d}t\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  Parameters `x` and `y`must be non-negative and at most one ot them  zero.
  //!  Parameter `z` must be greater than 0.
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
  //!  Higher-order function generating a masked version of eve::ellint_rd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_rd[cond](x, ...)` is equivalent to `if_else(cond,ellint_rd(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/elliptic/ellint_rd.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rd_, ellint_rd);
}

#include <eve/module/elliptic/regular/impl/ellint_rd.hpp>
