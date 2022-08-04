//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fsnm
//!   @brief Computes the fused negate substact multiply of its three parameters.
//!
//!   The call `fsnm(x, y, z)` is similar to `-x-y*z` as if calculated to infinite precision
//!   and rounded once to fit the result as much as supported by the hardware.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      eve::compatible_value_t fsnm(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `-x-y*z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonnable cost.
//!
//!    **Note**
//!
//!       This `fsnm` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/fsnm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fsnm[mask](x, ...)` provides a masked
//!     version of `fsnm` which is
//!     equivalent to `if_else(mask, fsnm(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/fsnm.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!       * The call `pedantic(fsnm)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//!
//!       * The call `numeric(fsnm)(x,y,z)` ensures the full compliance to fsnm properties.
//!        This can be very expensive if the system has no hardware capability.
//!
//!       * see the above regular example.
//! @}
//================================================================================================

//================================================================================================
//! @addtogroup core
//! @{
//! @var fsnm
//!
//! @brief Callable object computing the fused sub-negate-multiply operation.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
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
//! The call `fsnm(x, y, z)` is similar to `-x-y*z` as if calculated to infinite precision and
//! rounded once to fit the result as much as supported by the hardware.
//!
//! The result type is the [common compatible type](@ref common_compatible) of the three parameters.
//!
//!@warning Note
//!    This `fsnm` implementation provides those properties for all [integral real value](@ref
//!    eve::integral_value)
//!     and when possible for [floating real value](@ref eve::floating_value).
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
//!  A Callable object so that the expression `fsnm[cond](x, ...)` is equivalent to
//!  `if_else(cond,fsnm(x, ...),x)`
//!
//! ---
//!
//! #### Supported decorators
//!
//!  * eve::pedantic
//!
//!
//!     The call `pedantic(fsnm)(x,y,z)` ensures the one rounding property. This can be very
//!     expensive if the
//!      system has no hardware capability.
//!  * eve::numeric
//!
//!
//!     The call `numeric(fsnm)(x,y,z)` ensures the full compliance to fsnm properties. This can be
//!     very expensive if the
//!      system has no hardware capability.
//!
//!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
//!
//!
//!     The expression `diff_1st(fsnm)(x,y,z)`, `diff_2nd(fsnm)(x,y,z)` and `diff_3rd(fsnm)(x,y,z)`
//!     compute the partial
//!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ -x-y z\f$.
//!
//! #### Example
//!
//! @godbolt{doc/core/fsnm.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(fsnm_, fsnm);
}

#include <eve/module/core/regular/impl/fsnm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsnm.hpp>
#endif
