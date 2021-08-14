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
  //! @var fsnm
  //!
  //! @brief Callable object computing the fused sub-negate-multiply operation.
  //!
  //! **Required header:** `#include <eve/function/fsnm.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused sub-negate-multiply operation                    |
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
  //!`x`, `y`, `z`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!The call `fsnm(x, y, z)` is similar to `-x-y*z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the three parameters.
  //!
  //!@warning Note
  //!    This `fsnm` implementation provides those properties for all [real integral values](../../concepts.html#integral_value)
  //!     and when possible for [real floating values](@ref eve::value).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fsnm
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fsnm[cond](x, ...)` is equivalent to `if_else(cond,fsnm(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/fsnm.hpp>`
  //!
  //!     The call `pedantic(fsnm)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/fsnm.hpp>`
  //!
  //!     The call `numeric(fsnm)(x,y,z)` ensures the full compliance to fsnm properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/fsnm.hpp>`
  //!
  //!     The expression `diff_1st(fsnm)(x,y,z)`, `diff_2nd(fsnm)(x,y,z)` and `diff_3rd(fsnm)(x,y,z)` compute the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ -x-y z\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/fsnm.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fsnm_, fsnm);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fsnm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fsnm.hpp>
#endif
