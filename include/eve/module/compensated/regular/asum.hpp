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
  //! @addtogroup core
  //! @{
  //! @var asum
  //!
  //! @brief Callable object computing the asum operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the asum operation                                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!  template< range R> auto operator()( R xs ) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [value](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!In the first case The result type is the [common compatible type](@ref common_compatible) of the parameters,
  //!in the second the range value_type.
  //!
  //! The object function Computes the sum of the absolute values of the inputs
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::comp
  //!
  //!
  //!     The call `comp(asum)(x,args...`  computes the sum of the absolute values of its parameters
  //!      using kahan compensation algoritm.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/asum.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(asum_, asum);
}

#include <eve/module/compensated/regular/impl/asum.hpp>
