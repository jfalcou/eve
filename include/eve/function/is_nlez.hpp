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
  //! @addtogroup comparisons
  //! @{
  //! @var is_nlez
  //!
  //! @brief Callable object computing the "not less or equal to zero" predicate.
  //!
  //! **Required header:** `#include <eve/function/is_nlez.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "not less or equal to zero" predicate   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#value) `!(x <= 0)`.
  //!
  //!The result type is `logical< T >`.
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
  //! @include{lineno} doc/core/is_nlez.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct is_nlez_; }
  template<> struct supports_conditional<tag::is_nlez_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(is_nlez_, is_nlez);
}

#include <eve/module/real/core/function/regular/generic/is_nlez.hpp>
