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
//! @var sqr_abs
//!
//! @brief Callable object computing the sqr_abs operation.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! #### Members Functions
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | the sqr_abs operation                                      |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  auto operator()( floating_value auto x ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Computes  [elementwise](@ref glossary_elementwise) the square of the absolute value of `x`.
//!
//! ---
//!
//! #### Supported decorators
//!
//!  * eve::diff, eve::diff_1st, eve::diff_nth
//!
//!
//!     The expression `diff(sqr_abs)(x)` computes the derivative of the function at `x`.
//!
//! #### Example
//!
//! @godbolt{doc/core/sqr_abs.cpp}
//!
//!  @}
//================================================================================================

namespace tag
{
  struct sqr_abs_;
}
template<> struct supports_conditional<tag::sqr_abs_> : std::false_type
{};

EVE_MAKE_CALLABLE(sqr_abs_, sqr_abs);
}

#include <eve/module/core/regular/impl/sqr_abs.hpp>
