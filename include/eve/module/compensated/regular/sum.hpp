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
  //! @var sum
  //!
  //! @brief Callable object computing the sum operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sum operation                                         |
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
  //! The object function Computes the sum of the values of the inputs
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::comp
  //!
  //!
  //!     The call `comp(sum)(x,args...`  computes the sum of the values of its parameters
  //!      using kahan compensation algorihthm.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sum.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sum_, sum);
}

#include <eve/module/compensated/regular/impl/sum.hpp>
