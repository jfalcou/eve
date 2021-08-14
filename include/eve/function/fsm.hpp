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
  //! @var fsm
  //!
  //! @brief Callable object computing the fused sub-multiply operation.
  //!
  //! **Required header:** `#include <eve/function/fsm.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused sub-multiply operation   |
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
  //!The call `fsm(x, y, z)` is similar to `-x+y*z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the three parameters.
  //!
  //!@warning Note
  //!    This `fsm` implementation provides those properties for all [real integral values](../../concepts.html#integral_value)
  //!     and when possible for [real floating values](../../concepts.html#value).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fsm
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fsm[cond](x, ...)` is equivalent to `if_else(cond,fsm(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** #include <eve/function/pedantic/fsm.hpp>
  //!
  //!     The call `pedantic(fsm)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * eve::numeric
  //!
  //!     **Required header:** #include <eve/function/numeric/fsm.hpp>
  //!
  //!     The call `numeric(fsm)(x,y,z)` ensures the full compliance to fsm properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!
  //!  * `diff`
  //!
  //!     **Required header:** #include <eve/function/diff/fsm.hpp>
  //!
  //!     The expression `diff_1st(fsm)(x,y,z)`, `diff_2nd(fsm)(x,y,z)` and `diff_3rd(fsm)(x,y,z)` compute the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ -x+y z\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/fsm.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fsm_, fsm);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fsm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fsm.hpp>
#endif
