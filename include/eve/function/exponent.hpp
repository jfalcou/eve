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
  //! @brief Callable object performing the computation of the computation of the exponent value.
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
  //!    The exponent $e$ and mantissa $m$ of a floating point entry $x$ are related by
  //!    $x =  m\times 2^e$, with  $|m| \in [1, 2[$ (except for $x = \pm0, \pm\infty$ or is a Nan,
  //!    where $m=x$ and $e=0$ ).
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
