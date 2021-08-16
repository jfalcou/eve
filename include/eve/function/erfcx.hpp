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
  //! @addtogroup special
  //! @{
  //! @var erfcx
  //!
  //! @brief Callable object computing the normalized complementary error function \f$\mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
  //!
  //! **Required header:** `#include <eve/function/erfcx.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the erfcx operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](@ref glossary_elementwise) \f$\displaystyle \mbox{erfcx}(x)=\frac{2e^{x^2}}{\sqrt\pi}\int_{x}^{\infty} e^{-t^2}\mbox{d}t\f$
  //!
  //! The result type is of the same type as the  parameter.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::erfcx
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `erfcx[cond](x, ...)` is equivalent to `if_else(cond,erfcx(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/erfcx.hpp>`
  //!
  //!     The expression `diff(erfcx)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/erfcx.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(erfcx_, erfcx);
}

#include <eve/module/real/special/function/regular/generic/erfcx.hpp>
