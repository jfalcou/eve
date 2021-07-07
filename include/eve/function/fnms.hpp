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
  //! @var fnms
  //!
  //! @brief Callable object performing the computation of the fused negate-multiply-substract operation.
  //!
  //! **Required header:** `#include <eve/function/fnms.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused negate-multiply-substract operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept
  //!  requires compatible< T, U > && compatible< T, V >;
  //!  
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!The call `fnms(x, y, z)` is similar to `-x*y-z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the three parameters.
  //!
  //!@warning Note
  //!    This `fnms` implementation provides those properties for all [real integral values](../../concepts.html#integral_value)
  //!     and when possible for [real floating values](../../concepts.html#value).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fnms
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fnms[cond](x, ...)` is equivalent to `if_else(cond,fnms(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/fnms.hpp>
  //! 
  //!  
  //!     The call `pedantic(fnms)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/fnms.hpp>
  //! 
  //!  
  //!     The call `numeric(fnms)(x,y,z)` ensures the full compliance to fnms properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!  
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/fnms.hpp>
  //! 
  //!  
  //!     The expression `diff_1st(fnms)(x,y,z)`, `diff_2nd(fnms)(x,y,z)` and `diff_3rd(fnms)(x,y,z)` computes the partial
  //!      diffs of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ -xy-z\f$.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/fnms.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fnms_, fnms);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fnms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fnms.hpp>
#endif
