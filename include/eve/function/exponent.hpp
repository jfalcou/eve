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
  //! @var exponent
  //!
  //! @brief Callable object performing the computation of the exponent value.
  //!
  //! **Required header:** `#include <eve/function/exponent.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the exponent value   |
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
  //!    Computes the [element-wise](../../../glossary.html#element-wise_) ieee exponent of the floating value.
  //!
  //!    The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$ are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [1, 2[\f$.
  //!    (except for \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::exponent
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `exponent[cond](x, ...)` is equivalent to `if_else(cond,exponent(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/exponent.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exponent_, exponent);
}

#include <eve/module/real/core/function/regular/generic/exponent.hpp>
