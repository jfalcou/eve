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
  //! @addtogroup arithmetic
  //! @{
  //! @var geommean
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/geommean.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the mid-point operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the mid-point operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  template< floating_value T, floating_value ...Ts> auto operator()( T x, Ts... args ) const noexcept
  //!            requires (compatiblevalues< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y` or `x`, `args`, ...
  //!:   [floating values](../../concepts.html#value).
  //!
  //!
  //!
  //! **Return value**
  //!
  //!For two parameters \f$\sqrt{xy}\f$. No overflow occurs.
  //!
  //!For more than two parameters \f$\sqrt[n]{x_1x_2...x_n}\f$
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
  //!
  //!@WARNING
  //!    if the number of parameters is even and the product of the parameters is srictly negative the result is a Nan.
  //!
  //!    if the number of parameters is odd the result has the sign of the product of the parameters
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::geommean
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `geommean[cond](x, ...)` is equivalent to `if_else(cond,geommean(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff_nth`
  //!
  //!     **Required header: 
  //! 
  //!       #include <eve/function/diff/geommean.hpp>`
  //! 
  //!  
  //!     The expression `diff_nth< N >(geommean)(x,args...)` computes the partial
  //!      diff of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is similar to `geommean(x1,x2,...,xn)/(n*xN)`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/geommean.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(geommean_, geommean);
}

#include <eve/module/real/core/function/regular/generic/geommean.hpp>
