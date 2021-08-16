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
  //! @var oneminus
  //!
  //! @brief Callable object computing the oneminus operation.
  //!
  //! **Required header:** `#include <eve/function/oneminus.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the oneminus operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  [element-wise](@ref glossary_elementwise) `1-x` with the type of `x`.
  //!
  //!@warning
  //!    If an  [element](@ref glossary_element) of the expected result is not representable in
  //!    the result type, the corresponding result [element](@ref glossary_element) is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::oneminus
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `oneminus[cond](x, ...)` is equivalent to `if_else(cond,oneminus(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `saturated`
  //!
  //!     **Required header:** `#include <eve/function/saturated/oneminus.hpp>`
  //!  
  //!     The call `saturated(oneminus)(x)` is semantically equivalent to `saturated(sub)(One(as(x)), x)`
  //!      and is never undefined.
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/oneminus.hpp>`
  //!  
  //!     The expression `diff(oneminus)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/oneminus.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(oneminus_, oneminus);
}

#include <eve/module/real/core/function/regular/generic/oneminus.hpp>
