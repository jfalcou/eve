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
  //! @var ellint_d
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/ellint_d.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the ellint_d operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ellint_d operation   |
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
  //! computes the complete and incomplete D elliptic integrals  :
  //!
  //!$$\displaystyle F(\phi,k) = \int_0^{\phi} \frac{\sin^2 t}{\sqrt{1-k^2\sin^2 t}}\mbox{d}t$$
  //!
  //!The complete case corresponds to $\phi = \pi/2$.
  //!
  //!  - `k` must verify $k^2\sin^2\phi \le 1$ or the result is nan.
  //!
  //!  - In the complete case this means $|k| \le 1$.
  //!
  //!  In any other case the result is nan.
  //!
  //!!!! WARNING
  //!  Be aware that as $\pi/2$ is not exactly represented by floating point values the result of the incomplete
  //!  function with a $\phi$ value near $\pi/2$ can differ a lot with the result of the complete call.
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
  //!  Higher-order function generating a masked version of eve::ellint_d
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ellint_d[cond](x, ...)` is equivalent to `if_else(cond,ellint_d(x, ...),x)`
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
  //! @include{lineno} doc/core/ellint_d.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_d_, ellint_d);
}

#include <eve/module/real/elliptic/function/regular/generic/ellint_d.hpp>
