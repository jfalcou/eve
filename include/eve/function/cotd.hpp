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
  //! @var cotd
  //!
  //! @brief Callable object computing cotd.
  //!
  //! **Required header:** `#include <eve/function/cotd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of cotd   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) cotangent of the input expressed in degrees.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  As all direct trigonometric functions, `cotd` supports the restricted, small, medium and big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/cotd.hpp>`
  //!  
  //!     The expression `diff(cotd)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/cotd.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct cotd_; }
  template<> struct supports_conditional<tag::cotd_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(cotd_, cotd);
}

#include <eve/module/real/math/function/regular/generic/cotd.hpp>
