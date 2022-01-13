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
  //! @addtogroup arithmetic
  //! @{
  //! @var agm
  //!
  //! @brief Callable object computing the agm of two floating values.
  //!
  //! **Required header:** `#include <eve/function/agm.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the arithmetic-geometric mean  operation                   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  template< floating_value T, floating_value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                                    requires (compatiblevalues< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating point values](@ref eve::floating_real_values).
  //!
  //! **Return value**
  //!
  //!  the arithmetic-geometric mean of `x` and `y`. No overflow occurs. The two parameters must share the same sign.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::agm
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `agm[cond](x, y)` is equivalent to `if_else(cond,agm(x, y),x)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/agm.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(agm_, agm);
}

#include <eve/module/arithmetic/regular/impl/agm.hpp>
