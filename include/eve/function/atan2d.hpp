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
  //! @var atan2d
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/atan2d.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the atan2d operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the atan2d operation   |
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
  //!the arc tangent of $\frac{y}x$  in the range [-180 , +180] radians, is returned.
  //!The **IEEE** limiting values are almost all satisfied :
  //!
  //!     -  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
  //!     -  If `y` is $\pm0$ and `x` is strictly negative or $-0$, $\pm180$ is returned
  //!     -  If `y` is $\pm0$ and `x` is strictly positive or $+0$, $\pm0$ is returned
  //!     -  If `y` is $\pm\inft`y`$ and `x` is finite, $\pm90$ is returned
  //!     -  If `x` is $\pm0$ and `y` is strictly negative, $-90$ is returned
  //!     -  If `x` is $\pm0$ and `y` is strictly positive, $+90$  is returned
  //!     -  If `x` is $-\inft`y`$ and `y` is finite and positive, $+180$ is returned
  //!     -  If `x` is $-\inft`y`$ and `y` is finite and negative, $-180$ is returned
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
  //!  Higher-order function generating a masked version of eve::atan2d
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `atan2d[cond](x, ...)` is equivalent to `if_else(cond,atan2d(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/pedantic/atan2d.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The call `pedantic(atan2d)(`x`,`y`)` returns the same results as the regular call, but all
  //!      **IEEE** limiting values are satisfied :
  //!  
  //!       -  If `y` is $\pm\infty$ and `x` is $-\inft`y`$,$\pm135$ is returned
  //!       -  If `y` is $\pm\infty$ and `x` is $+\infty$, $\pm45$ is returned
  //!       -  If `x` is $\pm0$ and `y` is $\pm-0$, $-90$ is returned
  //!       -  If `x` is $\pm0$ and `y` is $\pm+0$, $+90$  is returned
  //!  
  //!  
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/atan2d.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff_1st(atan2d)(x,y)` and `diff_2nd(atan2d)(x,y)` computes the partial
  //!      diffs of $f$, where $f$ is the function $(x,y) \rightarrow \ \mbox{atan2d}(x,y)$.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/atan2d.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(atan2d_, atan2d);
}

#include <eve/module/real/math/function/regular/generic/atan2d.hpp>

