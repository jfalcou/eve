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
  //! @var csc
  //!
  //! @brief Callable object computing csc.
  //!
  //! **Required header:** `#include <eve/function/csc.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of csc   |
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
  //!Returns the [element-wise](@ref glossary_elementwise) cosecant of the input.
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
  //!  As all direct trigonometric functions, `csc` supports the eve::restricted, eve::small, eve::medium and eve::big decorators. Click
  //!  to see the [properties and rationale](../trigonometric.html)
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/csc.hpp>`
  //!  
  //!     The expression `diff(csc)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/csc.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct csc_; }
  template<> struct supports_conditional<tag::csc_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(csc_, csc);
}

#include <eve/module/real/core/function/regular/generic/csc.hpp>
