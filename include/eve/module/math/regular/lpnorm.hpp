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
  //! @var lpnorm
  //!
  //! @brief Callable object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n |x_i|^p\right)^{\frac1p} \f$.
  //!
  //! **Required header:** `#include <eve/function/lpnorm.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the lpnorm operation                                       |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value P, floating_value T, floating_value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                                    requires (compatiblevalues< P, T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`p`, `x`, `args`:   [floating values](@ref eve::floating_value)
  //!
  //! **Return value**
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::lpnorm
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `lpnorm[cond](x, ...)` is equivalent to `if_else(cond,lpnorm(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/lpnorm.hpp>`
  //!
  //!     The call `pedantic(lpnorm)(x,args...)`  computes the \f$l_p\f$ norm
  //!      without undue overflow or underflow at intermediate stages of the computation
  //!      and can be more accurate than the non decorated call.
  //!
  //!      Morever it returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/lpnorm.hpp>`
  //!
  //!     The expression `diff_< N >(lpnorm)(x,args...)` computes the partial
  //!      diff of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is the
  //!      `N`th parameter value divided by the `lpnorm` value.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/lpnorm.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(lpnorm_, lpnorm);
}

#include <eve/module/math/regular/impl/lpnorm.hpp>
