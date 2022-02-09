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
  //! @addtogroup exponential
  //! @{
  //! @var powm1
  //!
  //! @brief Callable object computing powm1: \f$x^y-1\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of powm1   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T, floating_real_value T> auto operator()( T x, U y ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) power minus one, with good accuracy,
  //!even when `y` is very small, or when `x` is close to 1.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::powm1
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `powm1[cond](x, ...)` is equivalent to `if_else(cond,powm1(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!
  //!     The expression `diff_1st(powm1)(x,y)` and `diff_2nd(powm1)(x,y)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ x^y-1\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/powm1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(powm1_, powm1);
}

#include <eve/module/math/regular/impl/powm1.hpp>
