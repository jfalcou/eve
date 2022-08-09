//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
//!   @var fnms
//!   @brief Computes the fused  negate multiply substract of its three parameters.
//!
//!   The call `fnms(x, y, z)` is similar to `-x*y-z` as if calculated to infinite precision
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
//!      eve::compatible_value_t fnms(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `-x*y-z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonable cost.
//!
//!    @note
//!       This `fnms` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/fnms.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fnms[mask](x, ...)` provides a masked
//!     version of `fnms` which is
//!     equivalent to `if_else(mask, fnms(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/fnms.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!       * The call `pedantic(fnms)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//!
//!       * The call `numeric(fnms)(x,y,z)` ensures the full compliance to fnms properties.
//!        This can be very expensive if the system has no hardware capability.
//!
//!       * see the above regular example.
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(fnms_, fnms);
}

#include <eve/module/core/regular/impl/fnms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fnms.hpp>
#endif
