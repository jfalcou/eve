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
//!   @var fanm
//!   @brief Computes the fused add negate multiply of its three parameters.
//!
//!   The call `fanm(x, y, z)` is similar to `x-y*z` as if calculated to infinite precision
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
//!      eve::common_value_t fanm(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `x-y*z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonable cost.
//!
//!    @note
//!       This `fanm` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fanm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fanm[mask](x, ...)` provides a masked
//!     version of `fanm` which is
//!     equivalent to `if_else(mask, fanm(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!       * The call `pedantic(fanm)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//!
//!       * The call `numeric(fanm)(x,y,z)` ensures the full compliance to fanm properties.
//!        This can be very expensive if the system has no hardware capability.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(fanm_, fanm);
}

#include <eve/module/core/impl/fanm.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/impl/simd/x86/fanm.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/impl/simd/arm/sve/fanm.hpp>
#endif
