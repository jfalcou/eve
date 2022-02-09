//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var fdim
  //!
  //! @brief Callable object computing the positive difference.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fdim operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T, real_value U> auto operator()( T x, U y ) const noexcept
  //!  requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:    [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!Returns the  [elementwise](@ref glossary_elementwise) positive difference between `x` and `y`:
  //! * if `x>y`,   x-y is returned
  //! * if `x<=y`,  +0 is returned
  //! * otherwise a `Nan` is returned
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fdim
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fdim[cond](x, ...)` is equivalent to `if_else(cond,fdim(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff<br>
  //!
  //!       The expression `diff_1st(fim)(x,y)` and `diff_2nd(fim)(x,y)` computes the partial
  //!       derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ \max(0,x-y)\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/fdim.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fdim_, fdim);
}

#include <eve/module/core/regular/impl/fdim.hpp>
