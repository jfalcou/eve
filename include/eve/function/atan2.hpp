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
  //!the arc tangent of \f$\frac{y}x\f$  in the range \f$[-\pi , +\pi]\f$ radians, is returned.
  //!The **IEEE** limiting values are almost all satisfied :
  //!
  //!     -  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
  //!     -  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm\pi\f$ is returned
  //!     -  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
  //!     -  If `y` is \f$\pm\inft`y`\f$ and `x` is finite, \f$\pm\frac\pi2\f$ is returned
  //!     -  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac\pi2\f$ is returned
  //!     -  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac\pi2\f$  is returned
  //!     -  If `x` is \f$-\inft`y`\f$ and `y` is finite and positive, \f$+\pi\f$ is returned
  //!     -  If `x` is \f$-\inft`y`\f$ and `y` is finite and negative, \f$-\pi\f$ is returned
  //!     -  If `x` is \f$+\inft`y`\f$ and `y` is finite and positive, \f$+0\f$ is returned
  //!     -  If `x` is \f$+\inft`y`\f$ and `y` is finite and negative, \f$-0\f$ is returned
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
  //!       -  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\frac{\pm3\pi}4\f$ is returned
  //!       -  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\frac{\pm\pi}4\f$ is returned
  //!       -  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac\pi2\f$ is returned
  //!       -  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac\pi2\f$  is returned
  //!  
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/atan2.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff_1st(atan2)(x,y)` and `diff_2nd(atan2)(x,y)` computes the partial
  //!      diffs of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ \mbox{atan2}(x,y)\f$.
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

