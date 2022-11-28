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
//!      eve::common_value_t fsnm(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [real or complex arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `-x-y*z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonnable cost.
//!
//!    @note
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

EVE_MAKE_CALLABLE(fsnm_, fsnm);
}

#include <eve/module/core/regular/impl/fsnm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsnm.hpp>
#endif
