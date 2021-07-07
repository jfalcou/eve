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
  //! @addtogroup exponential
  //! @{
  //! @var logspace_add
  //!
  //! @brief Callable object performing the computation of the logspace_add operation.
  //!
  //! **Required header:** `#include <eve/function/logspace_add.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logspace_add operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U, floating_value ...Ts> auto operator()( T arg0, U arg1, Ts... args ) const noexcept
  //!                                                    requires (compatiblevalues< T, U, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`arg0`, `arg1`, `args`, ...
  //!:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Similar to  `log(exp(arg0) + exp(arg1) + exp(args)...)`;.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::logspace_add
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `logspace_add[cond](x, ...)` is equivalent to `if_else(cond,logspace_add(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff_nth`
  //!
  //!     **Required header:**  #include <eve/function/diff/logspace_add.hpp>
  //! 
  //!  
  //!     The expression `diff_nth< N >(logspace_add)(arg0,arg1,args...)` computes the partial
  //!      diff of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise if the parameters are \f$x_1, ... x_n\f$ returns \f$\displaystyle\frac{e^{x_N}}{e^{x_1} + ... + e^{x_n}}\f$
  //!  
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/logspace_add.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logspace_add_, logspace_add);
}

#include <eve/module/real/math/function/regular/generic/logspace_add.hpp>
