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
  //! @addtogroup arithmetic
  //! @{
  //! @var frac
  //!
  //! @brief Callable object computing the fractional part of a value.
  //!
  //! **Required header:** `#include <eve/function/frac.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the fractional part of a value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns a value with the same type as `x`  containing the [element-wise](@ref glossary_elementwise) fractional part of `x` with the same sign as `x`.
  //!
  //!In particular:
  //! * If an [element](../../../glossary.html#value) of `x` is \f$\pm0\f$,  \f$\pm0\f$ is returned.
  //! * If an [element](../../../glossary.html#value) of `x` is \f$\pm\infty\f$ or `Nan`, a `Nan` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::frac
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `frac[cond](x, ...)` is equivalent to `if_else(cond,frac(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/frac.hpp>`
  //!
  //!     The expression `diff(frac)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/frac.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(frac_, frac);
}

#include <eve/module/real/core/function/regular/generic/frac.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/frac.hpp>
#endif
