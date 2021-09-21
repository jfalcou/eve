//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var fnma
  //!
  //! @brief Callable object computing the fused negate-multiply-add operation.
  //!
  //! **Required header:** `#include <eve/function/fnma.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the fused negate-multiply-add operation   |
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
  //!`x`, `y`, `z`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!The call `fnma(x, y, z)` is similar to `-x*y+z` as if calculated to infinite precision and rounded once
  //!to fit the result as much as supported by the hardware.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the three parameters.
  //!
  //!@warning Note
  //!    This `fnma` implementation provides those properties for all [integral real value](@ref eve::integral_real_value)
  //!     and when possible for [floating real value](@ref eve::floating_real_value).
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fnma
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fnma[cond](x, ...)` is equivalent to `if_else(cond,fnma(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/fnma.hpp>`
  //!
  //!     The call `pedantic(fnma)(x,y,z)` ensures the one rounding property. This can be very expensive if the
  //!      system has no hardware capability.
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/fnma.hpp>`
  //!
  //!     The call `numeric(fnma)(x,y,z)` ensures the full compliance to fnma properties. This can be very expensive if the
  //!      system has no hardware capability.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/fnma.hpp>`
  //!
  //!     The expression `diff_1st(fnma)(x,y,z)`, `diff_2nd(fnma)(x,y,z)` and `diff_3rd(fnma)(x,y,z)` compute the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ -xy+z\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/fnma.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fnma_, fnma);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fnma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fnma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/fnma.hpp>
#endif
