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
  //! @var atan2
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/atan2.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the atan2 operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the atan2 operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept
  //!  requires compatible< T,U>;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [value](../../concepts.html#value)
  //!
  //!
  //! **Return value**
  //!
  //!the arc tangent of $\frac{y}x$  in the range $[-\pi , +\pi]$ radians, is returned.
  //!The **IEEE** limiting values are almost all satisfied :
  //!
  //!     -  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
  //!     -  If `y` is $\pm0$ and `x` is strictly negative or $-0$, $\pm\pi$ is returned
  //!     -  If `y` is $\pm0$ and `x` is strictly positive or $+0$, $\pm0$ is returned
  //!     -  If `y` is $\pm\inft`y`$ and `x` is finite, $\pm\frac\pi2$ is returned
  //!     -  If `x` is $\pm0$ and `y` is strictly negative, $-\frac\pi2$ is returned
  //!     -  If `x` is $\pm0$ and `y` is strictly positive, $+\frac\pi2$  is returned
  //!     -  If `x` is $-\inft`y`$ and `y` is finite and positive, $+\pi$ is returned
  //!     -  If `x` is $-\inft`y`$ and `y` is finite and negative, $-\pi$ is returned
  //!     -  If `x` is $+\inft`y`$ and `y` is finite and positive, $+0$ is returned
  //!     -  If `x` is $+\inft`y`$ and `y` is finite and negative, $-0$ is returned
  //!     -  If either `x` is Nan or `y` is Nan, Nan is returned
  //!
  //!     The call will return a NaN if `x` and `y` are both either null or infinite: this result is not **IEEE** conform,
  //!     but not more absurd than the IEEE choices and allows to simplify (and speed) the implementation.
  //!     In all other cases, the result is standard conformant.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibilit`y`) of the two parameters.
  //!
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::atan2
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `atan2[cond](x, ...)` is equivalent to `if_else(cond,atan2(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/pedantic/atan2.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The call `pedantic(atan2)(`x`,`y`)` returns the same results as the regular call, but all
  //!      **IEEE** limiting values are satisfied :
  //!  
  //!       -  If `y` is $\pm\infty$ and `x` is $-\infty$, $\frac{\pm3\pi}4$ is returned
  //!       -  If `y` is $\pm\infty$ and `x` is $+\infty$, $\frac{\pm\pi}4$ is returned
  //!       -  If `x` is $\pm0$ and `y` is $\pm-0$, $-\frac\pi2$ is returned
  //!       -  If `x` is $\pm0$ and `y` is $\pm+0$, $+\frac\pi2$  is returned
  //!  
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/atan2.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff_1st(atan2)(x,y)` and `diff_2nd(atan2)(x,y)` computes the partial
  //!      diffs of $f$, where $f$ is the function $(x,y) \rightarrow \ \mbox{atan2}(x,y)$.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/atan2.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(atan2_, atan2);
}

#include <eve/module/real/math/function/regular/generic/atan2.hpp>

