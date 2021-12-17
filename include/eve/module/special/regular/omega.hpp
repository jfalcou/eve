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
  //! @addtogroup special
  //! @{
  //! @var omega
  //!
  //! @brief Callable object computing the Wright \$\omega\f$ function inverse of \$f x-> \log x+x\f$
  //!
  //! **Required header:** `#include <eve/function/omega.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the omega operation                                        |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [real_floating_value](@ref eve::real_floating_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the omega function.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/omega.hpp>`
  //!
  //!     The expression `diff(omega)(x)` computes the derivative  of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/special/omega.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(omega_, omega);
}

#include <eve/module/special/regular/impl/omega.hpp>
