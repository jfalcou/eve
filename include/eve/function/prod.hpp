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
  //! @addtogroup reduction
  //! @{
  //! @var prod
  //!
  //! @brief Callable object performing the computation of **TODO: FILL THIS BLANK**.
  //!
  //! **Required header:** `#include <eve/function/prod.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | **TODO: FILL THIS BLANK**   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<**TODO: FILL THIS BLANK**>
  //!  auto operator()( **TODO: FILL THIS BLANK**) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   **TODO: FILL THIS BLANK**
  //!
  //!OTHER PARAMETERS
  //!:   **TODO: FILL THIS BLANK IF NEEDED BUT RESPECT THE : FORMATTING**
  //!
  //! **Return value**
  //!
  //!For **TODO: FILL THIS BLANK**:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!auto r = prod(**TODO: FILL THIS BLANK**);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically equivalent to:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!Target r;
  //!
  //!if constexpr( scalar_value<T> )
  //!{
  //!  **TODO: FILL THIS BLANK**
  //!}
  //!else if constexpr( simd_value<T> )
  //!{
  //!  **TODO: FILL THIS BLANK**
  //!}
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::prod
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `prod[cond](x, ...)` is equivalent to `if_else(cond,prod(x, ...),x)`
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
  //! @include{lineno} doc/core/prod.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(prod_, prod);
}

#include <eve/module/real/core/function/scalar/prod.hpp>
//#include <eve/module/real/core/function/regular/simd/prod.hpp>
