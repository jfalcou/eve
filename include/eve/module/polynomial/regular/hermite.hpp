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
  //! @addtogroup polynomial
  //! @{
  //! @var hermite
  //!
  //! @brief Callable object computing the hermite operation.
  //!
  //! **Required header:** `#include <eve/hermite.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the hermite operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!   auto operator()( integral_real_value auto n, floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [integral real valuex](@ref eve::integral_real_value) or integral constant.
  //!
  //!`x`:   [floating valuex](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the 'physicists' hermite polynomial of order `n` at `x`:
  //!
  //!The result type is of the [common compatible type](@ref common_compatible) of the  parameters.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/diff/hermite.hpp>`
  //!
  //!     The expression `diff(hermite)(n,x)` computes the derivative of the function relative to `x`.
  //!
  //!  * eve::successor
  //!
  //!     The expression `successor(hermite)(n, x, Hn, Hnm1)` implements the three terms recurrence relation for the Hermite polynomials,
  //!     \f$\displaystyle \mbox{H}_{n+1} = (2*x)\mbox{H}_{n}-2*n\mbox{H}_{n-1}\f$
  //!
  //!     These object functions can be used to create a sequence of values evaluated at the same `x`, and for rising `n`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/hermite.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(hermite_, hermite);
}

#include <eve/module/polynomial/regular/impl/hermite.hpp>
