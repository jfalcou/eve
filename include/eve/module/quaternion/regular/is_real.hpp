//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var is_real
  //!
  //! @brief Callable object computing is_realinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | is the pure part of x 0             |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //! true  if `x` the pure  part of `x` if 0,  false otherwise
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/is_real.cpp}
  //!
  //!  @}
  //================================================================================================

}
