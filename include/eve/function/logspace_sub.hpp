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
  //! @var logspace_sub
  //!
  //! @brief Callable object performing the computation of the logspace_sub operation.
  //!
  //! **Required header:** `#include <eve/function/logspace_sub.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logspace_sub operation   |
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
  //!Supported decorators
  //!====================================================================================================
  //![`diff`](../decorators.html#diff)
  //!:   **Required header:** **<script type="preformatted">` #include <eve/function/diff/logspace_sub.hpp>`</script>
  //!
  //!:   The expression `diff_nth< N >(logspace_sub)(arg0,arg1,args...)` computes the partial
  //!    diff of the function relative to its Nth parameter. The returned value is 0 if N is
  //!    greater that the actual number of parameters, otherwise if the parameters are \f$x_1, ... x_n\f$ returns \f$\displaystyle\frac{s e^{x_N}}{e^{x_1} - ... - e^{x_n}}\f$
  //!    where \f$s\f$ is \f$1\f$ if \f$N = 1\f$ and \f$-1\f$ otherwise.
  //!
  //! **Return value**
  //!
  //!Similar to  `log(exp(arg0) - (exp(arg1) + exp(args)...))`;.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::logspace_sub
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `logspace_sub[cond](x, ...)` is equivalent to `if_else(cond,logspace_sub(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/logspace_sub.hpp>
  //!  
  //!     The expression `diff_nth< N >(logspace_sub)(arg0,arg1,args...)` computes the partial
  //!      diff of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise if the parameters are \f$x_1, ... x_n\f$ returns \f$\displaystyle\frac{s e^{x_N}}{e^{x_1} - ... - e^{x_n}}\f$
  //!      where \f$s\f$ is \f$1\f$ if \f$N = 1\f$ and \f$-1\f$ otherwise.
  //!  
  //!  Return value
  //!  ----------------------------------------------------------------------------------------------------
  //!  <span class="smallskip"></span>
  //!  Similar to  `log(exp(arg0) - (exp(arg1) + exp(args)...))`;.
  //!  
  //!   The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/logspace_sub.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logspace_sub_, logspace_sub);
}

#include <eve/module/real/math/function/regular/generic/logspace_sub.hpp>
