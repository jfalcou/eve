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
  //! @var ellint_rf
  //!
  //! @brief Callable object computing the Carlson's elliptic integral
  //!        \f$\frac12 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)(t+z)]^{-1/2}\scriptstyle\;\mathrm{d}t\f$
  //!
  //! **Required header:** #include <eve/module/elliptic.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rf operation                                    |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
 //!  auto operator()( floating_real_value auto x
  //!                , floating_real_value auto y)
  //!                , floating_real_value auto zconst noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [floating values](@ref eve::value).
  //!
  //!  This computes the Carlson's elliptic integral
  //!
  //!  \f[ R_F(x, y, z) = \frac12 \int_{0}^{\infty} [(t+x)(t+y)(t+z)]^{-1/2} \mbox{d}t\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  parameters must be non-negative and at most one zero or the result is nan.
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
  //!  Higher-order function generating a masked version of eve::ellint_rf
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_rf[cond](x, ...)` is equivalent to `if_else(cond,ellint_rf(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/elliptic/ellint_rf.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rf_, ellint_rf);
}

#include <eve/module/elliptic/regular/impl/ellint_rf.hpp>
