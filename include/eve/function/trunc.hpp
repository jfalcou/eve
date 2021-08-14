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
  //! @addtogroup rounding
  //! @{
  //! @var trunc
  //!
  //! @brief Callable object computing the trunc operation.
  //!
  //! **Required header:** `#include <eve/function/trunc.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the trunc operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Computes  [element-wise](@ref glossary_elementwise) the integral part of `x` with the same sign as  `x`.
  //!
  //!The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`, `FE_TOWARDZERO`.
  //!    This function object implements the `FE_TOWARDZERO` version.
  //!
  //!The call to `trunc(a)` is equivalent to the call `toward_zero(round)(a)`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::trunc
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `trunc[cond](x, ...)` is equivalent to `if_else(cond,trunc(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `tolerant`
  //!
  //!     **Required header:** `#include <eve/function/tolerant/trunc.hpp>`
  //!  
  //!     The expression `tolerant(trunc)(x, tol)` computes a tolerant truncated value for `x`, where `x` must be a floating value.
  //!  
  //!      - If `tol` is a floating_value computes the floor with a tolerance `tol` using Hagerty's FL5 function.
  //!      - If `tol` is an integral_value n compute the floor of the next nth representable value in the `x` type.
  //!      - If `tol` is omitted the tolerance is taken to 3 times the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/trunc.hpp>`
  //!  
  //!     The expression `diff(trunc)(x)` computes the derivative of the function at `x` .
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/trunc.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(trunc_, trunc);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/trunc.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/trunc.hpp>
#endif
