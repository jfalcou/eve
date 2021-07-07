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
  //! @var rat
  //!
  //! @brief Callable object performing the computation of the computation of the rational approximation.
  //!
  //! **Required header:** `#include <eve/function/rat.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the rational approximation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T> auto operator()( T x ) const noexcept;
  //!  template< floating_real_value T, floating_real_value S> auto operator()( T x, S tol) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_real_value](../../concepts.html#value).
  //!`tol`:   [floating_real_value](../../concepts.html#value).
  //!
  //! **Return values**
  //!
  //!Two values with the same type as `x` containing the [element-wise](../../../glossary.html#value) numerator and denominator of the rational number
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/rat.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rat_, rat);
}

#include <eve/module/real/core/function/regular/generic/rat.hpp>
