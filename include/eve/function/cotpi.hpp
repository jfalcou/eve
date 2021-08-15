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
  //! @var cotpi
  //!
  //! @brief Callable object computing cotpi.
  //!
  //! **Required header:** `#include <eve/function/cotpi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of cotpi   |
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
  //!Returns the [element-wise](@ref glossary_elementwise) cotine of the input expressed in \f$\pi\f$ multiples.
  //!
  //!The call `cotpi(x)` is semantically equivalent to \f$\cot(\pi x)\f$.
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  As all direct trigonometric functions, `cotpi` supports the eve::restricted, eve::small, eve::medium and eve::big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/cotpi.hpp>`
  //!
  //!     The expression `diff(cotpi)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/cotpi.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct cotpi_; }
  template<> struct supports_conditional<tag::cotpi_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(cotpi_, cotpi);
}

#include <eve/module/real/math/function/regular/generic/cotpi.hpp>
