//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var m1to
  //!
  //! @brief Callable object computing the m1to operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the m1to operation   |
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
  //!Computes  [elementwise](@ref glossary_elementwise) `1-x` with the type of `x`.
  //!
  //!@warning
  //!    If an  [element](@ref glossary_elementwise) of the expected result is not representable in
  //!    the result type, the corresponding result [element](@ref glossary_elementwise) is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::m1to
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `m1to[cond](x, ...)` is equivalent to `if_else(cond,m1to(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `saturated`
  //!
  //!  
  //!     The call `saturated(m1to)(x)` is semantically equivalent to `saturated(sub)(One(as(x)), x)`
  //!      and is never undefined.
  //!  
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!  
  //!     The expression `diff(m1to)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/m1to.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(m1to_, m1to);
}

#include <eve/module/core/regular/impl/m1to.hpp>
