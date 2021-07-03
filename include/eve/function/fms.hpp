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
  //! @var fms
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/fms.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the fused multiply-substract operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused multiply-substract operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept;
  //!  requires compatible< T,U> && compatible< T, V >;
  //!  
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](../../concepts.html#value)
  //!
  //!
  //! **Return value**
  //!
  //!The call `fms(x, y, z)` is similar to `x*y-z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the three parameters.
  //!
  //!
  //!@WARNING Note
  //!    This `fms` implementation provides those properties for all [real integral values](../../concepts.html#integral_value)
  //!     and when possible for [real floating values](../../concepts.html#value).
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fms
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fms[cond](x, ...)` is equivalent to `if_else(cond,fms(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!
  //!     **Required header:**  #include <eve/function/pedantic/fms.hpp>
  //! 
  //!  
  //!     The call `pedantic(fms)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * `numeric`
  //!
  //!     **Required header:**  #include <eve/function/numeric/fms.hpp>
  //! 
  //!  
  //!     The call `numeric(fms)(x,y,z)` ensures the full compliance to fms properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/fms.hpp>
  //! 
  //!  
  //!     The expression `diff_1st(fms)(x,y,z)`, `diff_2nd(fms)(x,y,z)` and `diff_3rd(fms)(x,y,z)` computes the partial
  //!      diffs of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ xy-z\f$.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/fms.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fms_, fms);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fms.hpp>
#endif

