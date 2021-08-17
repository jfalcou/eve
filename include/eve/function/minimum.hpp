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
  //! @addtogroup reduction
  //! @{
  //! @var minimum
  //!
  //! @brief Callable object computing **TODO: FILL THIS BLANK**.
  //!
  //! **Required header:** `#include <eve/function/minimum.hpp>`
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
  //!auto r = minimum(**TODO: FILL THIS BLANK**);
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
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::minimum
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minimum[cond](x, ...)` is equivalent to `if_else(cond,minimum(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/minimum.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minimum_, minimum);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/minimum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/algorithm/function/regular/simd/x86/minimum.hpp>
#endif
