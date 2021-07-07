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
  //! @var floor
  //!
  //! @brief Callable object performing the computation of the floor operation.
  //!
  //! **Required header:** `#include <eve/function/floor.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the floor operation   |
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
  //!Computes  [element-wise](../../../glossary.html#elment-wise) the greatest integer not greater than `x`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::floor
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `floor[cond](x, ...)` is equivalent to `if_else(cond,floor(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `tolerant`
  //!
  //!     **Required header:**  #include <eve/function/tolerant/floor.hpp>
  //! 
  //!  
  //!     The expression `tolerant(floor)(x, tol)` computes a tolerant floor value for `x`, where `x` must be a floating value..
  //!  
  //!      - If `tol` is a floating_value computes the floor with a tolerance `tol` using Hagerty's FL5 function.
  //!      - If `tol` is an integral_value n compute the floor of the next nth representable value in the `x` type.
  //!      - If `tol` is omitted the tolerance is taken to 3 times the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/floor.hpp>
  //! 
  //!  
  //!     The expression `diff(floor)(x)` computes the derivative of the function at `x`.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/floor.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(floor_, floor);
}

#include <eve/module/real/core/function/regular/generic/floor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/floor.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/floor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/floor.hpp>
#endif
