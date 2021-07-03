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
  //! @addtogroup trigonometric
  //! @{
  //! @var sinpic
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/sinpic.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the  computation of sinpic.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of sinpic   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#elment-wise) sine of the input times $\pi$  divided by the input times $\pi$.
  //!
  //!In particular:
  //!
  //!   * If the element is $\pm0$, $1$ is returned.
  //!   * If the element is $\pm\infty$, 0 is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sinpic
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sinpic[cond](x, ...)` is equivalent to `if_else(cond,sinpic(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/sinpic.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff(sinpic)(x)` computes the derivative of the function at `x`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/sinpic.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sinpic_, sinpic);
}

#include <eve/module/real/math/function/regular/generic/sinpic.hpp>
