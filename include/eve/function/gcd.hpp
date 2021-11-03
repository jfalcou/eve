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
  //! @addtogroup combinatorial
  //! @{
  //! @var gcd
  //!
  //! @brief Callable object computing greater common divisor.
  //!
  //! **Required header:** `#include <eve/function/gcd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | greater common divisor operation                           |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( real_value p, real_value n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`p`, `n`:   [real values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //!@warning
  //!    `p` and `n` can be of any [real values](@ref eve::value) type, but when the types are not integral
  //!    the greatest common divisor is defined only if `p` and `n` element are [flint](@ref eve::is_flint).
  //!    If any of the arguments is not flint
  //!    then the behavior is undefined.
  //!
  //! #### Supported decorators
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::gcd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `gcd[cond](x, ...)` is equivalent to `if_else(cond,gcd(x, ...),x)`
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/gcd.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(gcd_, gcd);
}

#include <eve/module/real/combinatorial/function/regular/generic/gcd.hpp>
