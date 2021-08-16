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
  //! @addtogroup elliptic
  //! @{
  //! @var ellint_rd
  //!
  //! @brief Callable object computing the  the Carlson's elliptic integral
  //!         \f$ \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2} (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
  //!
  //! **Required header:** `#include <eve/function/ellint_rd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_rd operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U, floating_scalar_value V> auto operator()(T x, U y, V z) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [floating values](@ref eve::value).
  //!
  //!  This computes the Carlson's elliptic integral
  //!
  //!  \f[ R_D(x, y, z) = \frac32 \int_{0}^{\infty} [(t+x)(t+y)]^{-1/2} (t+z)^{-3/2} \mbox{d}t\f]
  //!
  //!  as described in  Carlson, Numerische Mathematik, vol 33, 1 (1979)
  //!
  //!  Parameters `x` and `y`must be non-negative and at most one ot them  zero. Parameter `z` must be greater than 0.
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
  //! @godbolt{doc/core/ellint_rd.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rd_, ellint_rd);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_rd.hpp>
