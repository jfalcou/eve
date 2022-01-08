//==================================================================================================
/*
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var fls
  //!
  //! @brief Callable object computing the fls operation.
  //!
  //! **Required header:** `#include <eve/function/fls.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fls operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( unsigned_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [unsigned value](@ref eve::unsigned_value).
  //!
  //! **Return value**
  //!
  //!Computes [elementwise](@ref glossary_elementwise) the index or position of the last
  //!significant bit set to one in the word counting from the least significant bit position. The result
  //!is undefined for a zero input if the pedantic decorator is not used.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fls
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fls[cond](x, ...)` is equivalent to `if_else(cond,fls(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/abs.hpp>`
  //!
  //!     The expression `pedantic(fls)(x)` returns the size of the element type (an out of range index) if
  //!      the input is zero.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/fls.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fls_, fls);
}

#include <eve/module/real/core/function/regular/generic/fls.hpp>
