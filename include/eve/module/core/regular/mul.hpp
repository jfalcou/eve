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
//! @addtogroup core_arithmetic
//! @{
//!   @var mul
//!   @brief Computes the sum of its arguments.
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
//!      template< eve::value... Ts >
//!      eve::common_compatible_t<Ts ...> mul(Ts ... x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `... xs` :  [arguments](eve::value).
//!
//!    **Return value**
//!
//!    The value of the product of the arguments is returned.
//!
//!   @note
//!     Take care that for floating entries, the multiplication is only 'almost' associative.
//!     This call performs multiplications in reverse incoming order.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/mul.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::mul[mask](x, ...)` provides a masked
//!     version of `mul` which is
//!     equivalent to `if_else(mask, mul(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/mul.cpp}
//!
//!   * eve::saturated
//!
//!     The call `saturated(mul)(args...)` computes the saturated  multiplication `args...`.
//!     The saturation is obtained in the [common compatible type](@ref common_compatible)
//!     of the N parameters. The computation is done as if all arguments were
//!     converted to this type and the saturated multiplication applied recursively on all
//!     parameters. No overflow occurs.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/mul.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(mul_, mul);
}

#include <eve/module/core/regular/impl/mul.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mul.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/mul.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/mul.hpp>
#endif
