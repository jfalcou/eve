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
  //! @var two_add
  //!
  //! @brief Callable object computing the two_add operation.
  //!
  //! **Required header:** `#include <eve/function/two_add.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the two_add operation   |
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
  //!computes [element-wise](../../../glossary.html#element-wise_) a pair of values `[a,e]` such that:
  //!
  //!* `a` is `x+y`
  //!* `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`
  //!
  //!where \f$\oplus\f$ adds its two parameters with infinite precision.
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
  //! @include{lineno} doc/core/two_add.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct two_add_; }
  template<> struct supports_conditional<tag::two_add_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(two_add_, two_add);
}

#include <eve/module/real/core/function/regular/generic/two_add.hpp>
