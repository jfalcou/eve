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
  //! @var lambert
  //!
  //! @brief Callable object computing the lambert function inverse of \$f x-> xe^x\f$
  //!
  //! **Required header:** `#include <eve/function/lambert.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the lambert operation                                      |
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
  //!Returns [elementwise](@ref glossary_elementwise) the value of the lambert function.
  //!
  //! The result type is the kumi pair of the two branches values. The branches are not defined for input less than \f$e^{-1}\f$ in that case they return nan.
  //! As for input positive only one branch exist the two values returned are equal.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/lambert.hpp>`
  //!
  //!     The expression `diff(lambert)(x)` computes the derivative of each branch of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/lambert.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(lambert_, lambert);
}

#include <eve/module/real/special/function/regular/generic/lambert.hpp>
