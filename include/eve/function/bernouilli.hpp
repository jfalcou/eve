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
  //! @addtogroup combinatorial
  //! @{
  //! @var bernouilli
  //!
  //! @brief Callable object computing bernouilli numbers sequence.
  //!
  //! **Required header:** `#include <eve/function/bernouilli.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | bernouilli numbers sequence   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( unsigned_value auto n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //! The result element type is always double to try to avoid overflow
  //! and its cardinal is the same as the entry in case of an simd call.
  //!
  //!@warning
  //!    this function will overflow as soon as the input is even and greater than 260
  //!    But all odd index values are properly computed as they are all 0 except \f$b_1 = -1/2\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/bernouilli.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bernouilli_, bernouilli);
}

#include <eve/module/real/combinatorial/function/regular/generic/bernouilli.hpp>
