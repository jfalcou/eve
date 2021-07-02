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
  //! @addtogroup invtrigonometric
  //! @{
  //! @var acosd
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/acosd.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the  computation of acosd.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acosd   |
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
  //!Returns the [element-wise](../../../glossary.html#elment-wise) value in degrees of the arc cosine of the
  //!input in the range $[0 , 180]$.
  //!
  //!In particular:
  //!
  //!   * If the element is $1$, $+0$ is returned.
  //!   * If the element $|x| > 1$, `NaN` is returned.
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
  //!  Higher-order function generating a masked version of eve::acosd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `acosd[cond](x, ...)` is equivalent to `if_else(cond,acosd(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/acosd.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff(acosd)(x)` computes the derivative of the function at `x`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/acosd.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(acosd_, acosd);
}

#include <eve/module/real/math/function/regular/generic/acosd.hpp>
