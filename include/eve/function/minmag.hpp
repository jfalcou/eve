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
  //! @var minmag
  //!
  //! @brief Callable object performing the computation of the minmag operation.
  //!
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/minmag.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the minmag operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                       requires (compatible_values< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value)
  //!
  //!
  //! **Return value**
  //!
  //!the least absolute value is returned.
  //!
  //!For instance for two elemnts:
  //!
  //!  * If `|x| >  |y|`,  `y` is returned.
  //!  * If `|x| <  |y|`,  `x` is returned.
  //!  * Otherwise `min(x, y)` is returned.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
  //!
  //!@warning
  //!   If any element of the inputs is a `Nan`, the corresponding output element is system-dependent.
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::minmag
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minmag[cond](x, ...)` is equivalent to `if_else(cond,minmag(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/minmag.hpp>
  //! 
  //!  
  //!  The behaviour is the same except that if  `|x| == |y|`, `pedantic(min)` is used.
  //!  
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/minmag.hpp>
  //! 
  //!  
  //!  The behaviour is the same except that if  `|x| == |y|`, `numeric(min)` is used.
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/minmag.hpp>
  //! 
  //!  
  //!     The expression `diff< N >(minmag)(x,args,...)` computes the partial
  //!      diff relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their minmag is \f$m\f$, the value returned is elementwise 1 if \f$m\f$ is equal to \f$x_N\f$ else 0.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/minmag.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minmag_, minmag);
}

#include <eve/module/real/core/function/regular/generic/minmag.hpp>

