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
  //! @addtogroup ieee754
  //! @{
  //! @var frexp
  //!
  //! @brief Callable object performing the computation of the computation of the frexp pair of values.
  //!
  //! **Required header:** `#include <eve/function/frexp.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the frexp pair of values   |
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
  //!`x`:   [floating_real_value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!    Computes the [element-wise](../../../glossary.html#element-wise_) ieee frexp of the floating value,
  //!    returning a pair {m,e} of values of the same type of `x` which are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
  //!
  //!    However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::frexp
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `frexp[cond](x, ...)` is equivalent to `if_else(cond,frexp(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/frexp.hpp>
  //! 
  //!  
  //!     The call `pedantic(frexp)(x)` takes also properly care of the cases where \f$x = \pm0, \pm\infty\f$ or is a Nan,
  //!      where \f$m=x\f$ and \f$e=0\f$ and of the denormal cases.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/frexp.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(frexp_, frexp);
}

#include <eve/module/real/core/function/regular/generic/frexp.hpp>
