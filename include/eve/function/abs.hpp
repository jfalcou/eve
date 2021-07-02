//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var abs
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/abs.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the absolute value.
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
  //!  auto operator()(eve::value auto const& x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `x`:  An instance of eve::value
  //!
  //! **Return value**
  //!
  //! A value with the same type as `x` containing the [elementwise](@ref glossary_elementwise)
  //! absolute value of `x` if it is representable in this type. More specifically, for signed
  //! integers the absolute value of eve::valmin is not representable and the result is undefined.
  //!
  //! @warning  `abs` is also a standard library function name and there possibly exists a C macro
  //! version which may be called instead of the **EVE** version.<br/>
  //! To avoid this, use the eve::abs notation.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::abs
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `abs[cond](x)` is equivalent to `if_else(cond,abs(x),x)`
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
  //!     The expression `eve::saturated(eve::abs)(x)` computes the saturated absolute value of `x`.
  //!     More specifically, for any signed integer value `x`, the expression
  //!     `eve::saturated(eve::abs)(eve::valmin(as(x)))` evaluates to `eve::valmax(as(x))`.
  //!
  //!   * eve::diff
  //!
  //!
  //!     **Required header:** `#include <eve/function/diff/abs.hpp>`
  //!
  //!     The expression `eve::diff( eve::abs )(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/Wevnjdb8n)
  //!
  //! @include{lineno} doc/core/abs.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(abs_, abs);
}

#include <eve/module/real/core/function/regular/generic/abs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/abs.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/abs.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/abs.hpp>
#endif
