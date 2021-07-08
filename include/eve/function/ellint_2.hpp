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
  //! @var ellint_2
  //!
  //! @brief Callable object performing the computation of the elliptic integrals of the second kind :
  //!        \f$ \int_0^{\phi} \scriptstyle \sqrt{1-k^2\sin^2 t} \scriptstyle\;\mathrm{d}t\f$
  //!
  //! **Required header:** `#include <eve/function/ellint_2.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_2 operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T>                   auto operator()(T k) const noexcept;
  //!  template< floating_value T, floating_value U> auto operator()(T phi, U k) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`phi`, `k`:   [floating values](../../concepts.html#value).
  //!
  //! computes the complete and incomplete elliptic integrals of the second kind :
  //!
  //!\f[ F(\phi,k) = \int_0^{\phi} \sqrt{1-k^2\sin^2 t}\mbox{d}t\f]
  //!
  //!The complete case corresponds to \f$\phi = \pi/2\f$.
  //!
  //!  - `k` must verify \f$k^2\sin^2\phi \le 1\f$ or the result is nan.
  //!
  //!  - In the complete case this means \f$|k| \le 1\f$.
  //!
  //!  In any other case the result is nan.
  //!
  //!!!! WARNING
  //!  Be aware that as \f$\pi/2\f$ is not exactly represented by floating point values the result of the incomplete
  //!  function with a \f$\phi\f$ value near \f$\pi/2\f$ can differ a lot with the result of the complete call.
  //!
  //! **Return value**
  //!
  //!Returns  [element-wise](../../../glossary.html#value) the elliptic integral of the first kind.
  //!
  //! The result type is of the compatibility type of the three parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ellint_2
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_2[cond](x, ...)` is equivalent to `if_else(cond,ellint_2(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/ellint_2.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_2_, ellint_2);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_2.hpp>
