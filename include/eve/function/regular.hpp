//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //! @var regular
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/regular.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of **TODO: FILL THIS BLANK**.
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
  //!
  //! **Return value**
  //!
  //!For **TODO: FILL THIS BLANK**:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!auto r = regular(**TODO: FILL THIS BLANK**);
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
  //!  Higher-order function generating a masked version of eve::regular
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `regular[cond](x, ...)` is equivalent to `if_else(cond,regular(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  decorators NOT FOUND
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/regular.cpp
  //!
  //!  @}
  //================================================================================================
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct regular_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - regular mode
  inline constexpr regular_type const regular = {};
}

