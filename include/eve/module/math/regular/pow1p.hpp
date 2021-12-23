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
  //! @var pow1p
  //!
  //! @brief Callable object computing pow1p: \f$x^y-1\f$.
  //!
  //! **Required header:** `#include <eve/function/pow1p.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of pow1p                                  |
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
  //!Returns the [elementwise](@ref glossary_elementwise) power(1+x, y), with good accuracy,
  //!even when `x` is  small.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::pow1p
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `pow1p[cond](x, ...)` is equivalent to `if_else(cond,pow1p(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/pow.hpp>`
  //!
  //!     The expression `diff_1st(pow1p)(x,y)` and `diff_2nd(pow1p)(x,y)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ (1+x)^y\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/pow1p.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pow1p_, pow1p);
}

#include <eve/module/math/regular/impl/pow1p.hpp>
