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
  //! @addtogroup combinatorial
  //! @{
  //! @var factorial
  //!
  //! @brief Callable object computing unsigned integral factorial \f$\displaystyle n! = \prod_{i=1}^n i\f$.
  //!
  //! **Required header:** `#include <eve/function/factorial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | unsigned integral factorial   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< unsigned_value T > auto operator()( T n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //! The result element type is always double to try to avoid overflow
  //! and its cardinal is the same as the entry in case of an simd call.
  //!
  //!@warning
  //!    this function will overflow as soon as the input is greater than 171
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
  //! @include{lineno} doc/core/factorial.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct factorial_; }
  template<> struct supports_conditional<tag::factorial_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(factorial_, factorial);
}

#include <eve/module/real/combinatorial/function/regular/generic/factorial.hpp>
