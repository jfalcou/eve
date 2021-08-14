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
  //! @addtogroup trigonometric
  //! @{
  //! @var cos
  //!
  //! @brief Callable object computing cos.
  //!
  //! **Required header:** `#include <eve/function/cos.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of cos   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) cosine of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `Nan`, `Nan` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  As all direct trigonometric functions, `cos` supports the restricted, small, medium and big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/cos.hpp>`
  //!  
  //!     The expression `diff(cos)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/cos.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct cos_; }
  template<> struct supports_conditional<tag::cos_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(cos_, cos);
}

#include <eve/module/real/math/function/regular/generic/cos.hpp>
