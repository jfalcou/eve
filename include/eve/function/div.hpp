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
  //! @var div
  //!
  //! @brief Callable object performing the division of multiple values.
  //!
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/div.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the absolute value of its parameter               |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const&... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `xs`:  Instances of eve::value. Behavior is undefined if any `xs` is integral and equal to 0.
  //!
  //! **Return value**
  //!
  //! A value of the [common compatible type](@ref common_compatible) of all `xs` containing the
  //! [elementwise](@ref glossary_elementwise) division of all `xs`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::div
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `div[cond](x0,xs...)` is equivalent
  //!  to `if_else(cond,div(x0,xs...),x0)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!
  //!     **Required header:** `#include <eve/function/saturated/abs.hpp>`
  //!
  //!     The expression `eve::saturated(eve::div)(xs...)` computes the saturated division of
  //!     all `xs`.
  //!
  //!   * eve::diff
  //!
  //!
  //!     **Required header:** `#include <eve/function/diff/div.hpp>`
  //!
  //!     The expression `eve::diff<N>(eve::div)(xs...)` computes the derivative of the division
  //!     of `xs...` over the Nth parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/4M9PrKGWE)
  //!
  //! @include{lineno} doc/core/div.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(div_, div);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/div.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/div.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/div.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/div.hpp>
#endif
