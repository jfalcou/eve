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
  //! @addtogroup invtrigonometric
  //! @{
  //! @var acsc
  //!
  //! @brief Callable object computing acsc.
  //!
  //! **Required header:** `#include <eve/function/acsc.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acsc   |
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
  //!Returns the [element-wise](../../../glossary.html#elment-wise) arc cosecant of the
  //!input in the range \f$[-\pi/2 , \pi/2]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm1\f$, \f$\pm\frac\pi2\f$ is returned.
  //!   * If the element \f$|x| < 1\f$, `NaN` is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/acsc.hpp>
  //!  
  //!     The expression `diff(acsc)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/acsc.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct acsc_; }
  template<> struct supports_conditional<tag::acsc_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(acsc_, acsc);
}

#include <eve/module/real/math/function/regular/generic/acsc.hpp>
