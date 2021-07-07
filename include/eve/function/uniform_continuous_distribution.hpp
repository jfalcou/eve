//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

#include <eve/module/real/proba/function/regular/generic/uniform_continuous_distribution.hpp>

  //================================================================================================
  //! @addtogroup proba
  //! @{
  //! @var uniform_continuous_distribution
  //!
  //! @brief Callable object performing the computation of   //!  description NOT FOUND.
  //!
  //! **Required header:** `#include <eve/function/uniform_continuous_distribution.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` |   //!  description NOT FOUND   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!    template< floating_real_value T> struct uniform_continuous_distribution;
  //!  }
  //!  
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!  parameters NOT FOUND
  //!
  //! **Return value**
  //!
  //!  return values NOT FOUND
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::uniform_continuous_distribution
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `uniform_continuous_distribution[cond](x, ...)` is equivalent to `if_else(cond,uniform_continuous_distribution(x, ...),x)`
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
  //! @include{lineno} doc/core/uniform_continuous_distribution.cpp
  //!
  //!  @}
  //================================================================================================z
