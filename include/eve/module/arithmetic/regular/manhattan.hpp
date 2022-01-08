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
  //! @var manhattan
  //!
  //! @brief Callable object computing the manhattan operation.
  //!
  //! **Required header:** `#include <eve/function/manhattan.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the manhattan operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                                    requires (compatiblevalues< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [value](@ref eve::value)
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
  //!  Higher-order function generating a masked version of eve::manhattan
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `manhattan[cond](x, ...)` is equivalent to `if_else(cond,manhattan(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/manhattan.hpp>`
  //!
  //!     The call `pedantic(manhattan)(x,args...`  computes the sum of the absolute values of its parameters
  //!      returning \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/manhattan.hpp>`
  //!
  //!     The expression `diff_< N >(manhattan)(x,args...)` computes the partial
  //!      derivative of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is the [sign](./sign.html) of the `N`th parameter value.
  //!
  //!  !!! Warning
  //!      This is only available for floating point entries.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/manhattan.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(manhattan_, manhattan);
}

#include <eve/module/real/core/function/regular/generic/manhattan.hpp>
