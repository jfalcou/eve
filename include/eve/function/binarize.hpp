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
  //! @addtogroup logical
  //! @{
  //! @var binarize
  //!
  //! @brief Callable object performing the computation of the binarize operation.
  //!
  //! **Required header:** `#include <eve/function/binarize.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the binarize operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, scalar_value V > T operator()( Logical< T >  c, V v = 1 ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`c`:   [logical value](../../concepts.html#value).
  //!`v`:   [scalar value](../../concepts.html#value) defaulting to 1.
  //!
  //! **Return value**
  //!
  //!The call:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r = binarize(c,v);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically  equivalent to:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!T r = if_else(c, T(v), T(0);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::binarize
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `binarize[cond](x, ...)` is equivalent to `if_else(cond,binarize(x, ...),x)`
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
  //! @include{lineno} doc/core/binarize.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(binarize_, binarize);
}

#include <eve/module/real/core/function/regular/generic/binarize.hpp>
