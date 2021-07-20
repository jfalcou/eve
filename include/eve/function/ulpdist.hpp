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
  //! @addtogroup ieee754
  //! @{
  //! @var ulpdist
  //!
  //! @brief Callable object computing the ulpdistt operation.
  //!
  //! **Required header:** `#include <eve/function/ulpdist.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ulpdistt operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!computes [element-wise](../../../glossary.html#element-wise_) the 'units in the last place' distance betwween `x` and `y`.
  //!This is semantically equivalent to:`
  //!
  //!* if is_ordered(x,y), nb_values(x,y)/2.0 is returned
  //!* otherwise a `Nan` is returned
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
  //! @include{lineno} doc/core/ulpdist.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ulpdist_, ulpdist);
}

#include <eve/module/real/core/function/regular/generic/ulpdist.hpp>
