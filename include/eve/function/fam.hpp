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
  //! @var fam
  //!
  //! @brief Callable object computing the fused add-multiply operation.
  //!
  //! **Required header:** `#include <eve/function/fam.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused add-multiply operation                           |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept
  //!  requires compatible< T,U> && compatible< T, V >;
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!The call `fam(x, y, z)` is similar to `x+y*z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the three parameters.
  //!
  //!@warning Note
  //!    This `fam` implementation provides those properties for all [real integral values](../../concepts.html#integral_value)
  //!     and when possible for [real floating values](../../concepts.html#value).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fam
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fam[cond](x, ...)` is equivalent to `if_else(cond,fam(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `pedantic`
  //!
  //!     **Required header:** #include <eve/function/pedantic/fam.hpp>
  //!
  //!     The call `pedantic(fam)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * `numeric`
  //!
  //!     **Required header:** #include <eve/function/numeric/fam.hpp>
  //!
  //!     The call `numeric(fam)(x,y,z)` ensures the full compliance to fam properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!
  //!  * `diff`
  //!
  //!     **Required header:** #include <eve/function/diff/fam.hpp>
  //!
  //!     The expression `diff_1st(fam)(x,y,z)`, `diff_2nd(fam)(x,y,z)` and `diff_3rd(fam)(x,y,z)` compute the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ x+y z\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/fam.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fam_, fam);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fam.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fam.hpp>
#endif

// #if defined(EVE_INCLUDE_POWERPC_HEADER)
// #  include <eve/module/real/core/function/regular/simd/ppc/fam.hpp>
// #endif

// #if defined(EVE_INCLUDE_ARM_HEADER)
// #  include <eve/module/real/core/function/regular/simd/arm/neon/fam.hpp>
// #endif
