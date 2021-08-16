//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var hypot
  //!
  //! @brief Callable object computing the hypot operation.
  //!
  //! **Required header:** `#include <eve/function/hypot.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the hypot operation   |
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
  //!The result type is the [common compatible type](@ref common_compatible) of the three parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::hypot
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `hypot[cond](x, ...)` is equivalent to `if_else(cond,hypot(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/hypot.hpp>`
  //!
  //!     The call `pedantic(hypot)(x,args...)`  computes the square root of the sum of the parameters
  //!      without undue overflow or underflow at intermediate stages of the computation
  //!      and can be more accurate than the [`regular`](../decorators.html#regular) call.
  //!
  //!      Morever it returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/hypot.hpp>`
  //!
  //!     The expression `diff_< N >(hypot)(x,args...)` computes the partial
  //!      derivativ of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is the
  //!      `N`th parameter value divided by the `hypot` value.
  //!
  //!  !!! Warning
  //!      This is only available for floating point entries.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/hypot.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(hypot_, hypot);
}

#include <eve/module/real/core/function/regular/generic/hypot.hpp>
