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
  //! @addtogroup logical
  //! @{
  //! @var ifnot_else
  //!
  //! @brief Callable object performing the computation of the ifnot_else operation.
  //!
  //! **Required header:** `#include <eve/function/ifnot_else.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ifnot_else operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept
  //!  requires  compatible< U, V >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!The call `ifnot_else(x, y, z)` is performs a choice between the elements of `y` and `z` according to the truth value
  //!of the elements of `x`. It is merely syntaxic sugar for `if_else(x, z, y)`
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
  //! @include{lineno} doc/core/ifnot_else.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ifnot_else_, ifnot_else);
}

#include <eve/module/real/core/function/regular/generic/ifnot_else.hpp>
