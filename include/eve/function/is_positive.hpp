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
  //! @addtogroup predicates
  //! @{
  //! @var is_positive
  //!
  //! @brief Callable object performing the computation of the computation of the is_positive logical value.
  //!
  //! **Required header:** `#include <eve/function/is_positive.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_positive logical value   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!For signed types The call `is_positive(x)` [element-wise](../../../glossary.html#value) returns true
  //!if and only if the bit of sign (most significant bit) is unset.
  //!
  //!@warning
  //!   this function coincides with `is_gez` on [integral real values](../../concepts.html#value),
  //!   but for [floating real values](../../concepts.html#value) `T`, `is_positive(Mzero<`T`>)` is false and
  //!   if `x` is a Nan the result depends of the bit of sign of `x` which can be out of control although
  //!   not undefined.
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
  //! @include{lineno} doc/core/is_positive.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_positive_, is_positive);
}

#include <eve/module/real/core/function/regular/generic/is_positive.hpp>
