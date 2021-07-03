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
  //! @addtogroup predicates
  //! @{
  //! @var is_odd
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/is_odd.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the computation of the is_odd logical value.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_odd logical value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //!
  //! **Return value**
  //!
  //!
  //!The call:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r = is_odd(x);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!computation is semantically  equivalent to:
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r;
  //!if constexpr(floating_real_value<T>)   r =  (a != dec(a)) && is_even(dec(a));
  //!else constexpr(integral_real_value<T>) r = is_equal(x, (x/2)*2);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_odd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_odd[cond](x, ...)` is equivalent to `if_else(cond,is_odd(x, ...),x)`
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
  //! @include{lineno} doc/core/is_odd.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_odd_, is_odd);
}

#include <eve/module/real/core/function/regular/generic/is_odd.hpp>

