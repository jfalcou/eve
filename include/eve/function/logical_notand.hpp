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
  //! @addtogroup logical
  //! @{
  //! @var logical_notand
  //!
  //! @brief Callable object computing the element-wise NOTAND operation.
  //!
  //! **Required header:** `#include <eve/function/logical_notand.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the element-wise NOTAND operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  element-wise NOTAND of the two parameters following the
  //![element-wise operations semantic](../../../glossary.html#Logicalwise).
  //!
  //!the call `logical_notand(x, y)` is semantically equivalent to `!x && y`
  //!if `x` or  `y` is an  [simd value](@ref eve::value).
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
  //! @include{lineno} doc/core/logical_notand.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_notand_; }
  template<> struct supports_conditional<tag::logical_notand_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_notand_, logical_notand);
}

#include <eve/module/real/core/function/regular/generic/logical_notand.hpp>
