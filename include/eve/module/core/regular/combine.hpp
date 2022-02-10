/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/as_wide.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup swar
  //! @{
  //! @var combine
  //!
  //! @brief Callable object computing **TODO: FILL THIS BLANK**.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
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
  //!auto r = combine(**TODO: FILL THIS BLANK**);
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
  //!  Higher-order function generating a masked version of eve::combine
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `combine[cond](x, ...)` is equivalent to `if_else(cond,combine(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/combine.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(combine_, combine);
}

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_),T const &a,T const &b) noexcept
  {
    return as_wide_t<T, typename cardinal_t<T>::combined_type>(a, b);
  }
}
