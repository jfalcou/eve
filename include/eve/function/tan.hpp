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
  //! @var tan
  //!
  //! @brief Callable object computing tan.
  //!
  //! **Required header:** `#include <eve/function/tan.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of tan   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) tangent of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  As all direct trigonometric functions, `tan` supports the eve::restricted, eve::small, eve::medium and eve::big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/tan.hpp>`
  //!  
  //!     The expression `diff(tan)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/tan.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct tan_; }
  template<> struct supports_conditional<tag::tan_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(tan_, tan);
}

#include <eve/module/real/math/function/regular/generic/tan.hpp>
