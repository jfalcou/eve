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
  //! @var ellint_1
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/ellint_1.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the ellint_1 operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_1 operation   |
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
  //!`phi, `k`:   [floating values](../../concepts.html#value).
  //!
  //!
  //! computes the complete and incomplete elliptic integrals of the first kind :
  //!
  //!\f[ F(\phi,k) = \int_0^{\phi} \frac{\mbox{d}t}{\sqrt{1-k^2\sin^2 t}}\f]
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
  //!
  //! **Return value**
  //!
  //!  return values NOT FOUND
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ellint_1
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_1[cond](x, ...)` is equivalent to `if_else(cond,ellint_1(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  decorators NOT FOUND
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/ellint_1.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_1_, ellint_1);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_1.hpp>
