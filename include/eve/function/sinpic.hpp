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
  //! @var sinpic
  //!
  //! @brief Callable object computing sinpic.
  //!
  //! **Required header:** `#include <eve/function/sinpic.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of sinpic   |
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
  //!Returns the [element-wise](@ref glossary_elementwise) sine of the input times \f$\pi\f$  divided by the input times \f$\pi\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, 0 is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/sinpic.hpp>`
  //!  
  //!     The expression `diff(sinpic)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/sinpic.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct sinpic_; }
  template<> struct supports_conditional<tag::sinpic_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(sinpic_, sinpic);
}

#include <eve/module/real/math/function/regular/generic/sinpic.hpp>
