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
//! @var sign
//!
//! @brief Callable object computing the sign operation.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! #### Members Functions
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | the sign operation   |
//! | `operator[]` | Construct a conditional version of current function object |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template< value T > auto operator()( T x ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//!`x`:   [value](@ref eve::value).
//!
//! **Return value**
//!
//! Computes  [elementwise](@ref glossary_elementwise) the sign of `x`.
//!
//! For [real value](@ref eve::value) `x` is semantically equivalent to:
//!  * If x is greater than 0, 1 is returned.
//!  * If x is less than 0,  -1 is returned.
//!  * If x is zero, x is returned.
//!
//! Moreover for  [floating real value](@ref eve::floating_value)
//! if x is `Nan`, the result is `Nan`
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  auto operator[]( conditional_expression auto cond ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//!  Higher-order function generating a masked version of eve::sign
//!
//!  **Parameters**
//!
//!  `cond` : conditional expression
//!
//!  **Return value**
//!
//!  A Callable object so that the expression `sign[cond](x, ...)` is equivalent to
//!  `if_else(cond,sign(x, ...),x)`
//!
//! ---
//!
//! #### Supported decorators
//!
//!  * eve::diff, eve::diff_1st, eve::diff_nth
//!
//!
//!     The expression `diff(sign)(x)` computes the derivative of the function at `x`.
//!
//! #### Example
//!
//! @godbolt{doc/core/sign.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(sign_, sign);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/sign.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sign.hpp>
#endif
