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
  //! @addtogroup trigonometric
  //! @{
  //! @var quadrant
  //!
  //! @brief Callable object computing the quadrant value.
  //!
  //! **Required header:** `#include <eve/function/quadrant.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the quadrant value   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!return a value of the same type as `x` containing the quadrant number where `x` (supposed an integer) lies.
  //!
  //!@warning
  //!   the input `x` must be an integral or floating integral value.
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
  //! @include{lineno} doc/core/quadrant.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct quadrant_; }
  template<> struct supports_conditional<tag::quadrant_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(quadrant_, quadrant);
}

#include <eve/module/real/core/function/regular/generic/quadrant.hpp>
