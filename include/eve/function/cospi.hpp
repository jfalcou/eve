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
  //! @var cospi
  //!
  //! @brief Callable object computing cospi.
  //!
  //! **Required header:** `#include <eve/function/cospi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of cospi   |
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
  //!Returns the [element-wise](@ref glossary_elementwise) cosine of the input expressed in \f$\pi\f$ multiples.
  //!
  //!The call `cospi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  As all direct trigonometric functions, `cospi` supports the restricted, small, medium and big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/cospi.hpp>`
  //!
  //!     The expression `diff(cospi)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/cospi.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct cospi_; }
  template<> struct supports_conditional<tag::cospi_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(cospi_, cospi);
}

#include <eve/module/real/math/function/regular/generic/cospi.hpp>
