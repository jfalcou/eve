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
//!   @var average
//!   @brief Computes the  arithmetic mean  of its arguments.
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
//!      template< eve::value T, eve::value U >
//!      eve::common_compatible_t<T, U> average(T x, U y) noexcept;
//!
//!      template< eve::floating_value Ts ... >
//!      eve::common_compatible_t<Ts ...> average(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [real](@ref eve::value) or [complex](@ref eve::complex) arguments.
//!
//!     * `xs...` :  [real](@ref eve::floating_value) or [complex](@ref eve::complex) arguments.
//!
//!    **Return value**
//!
//!    The value of the arithmetic mean  of the arguments is returned.
//!
//!   @note
//!     * For two parameters half the sum of `x` and `y`. No overflow occurs.
//!
//!     * For more than two parameters only floating or complex entries are allowed. No overflow occurs.
//!
//!     * If `x` and `y` are [integral values](@ref eve::integral_value) and the sum is odd, the
//!     result
//!       is a rounded value at a distance guaranteed
//!       to be less than or equal to 0.5 of the average floating value, but may differ
//!       by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
//!       simd intrinsics to perform the operation, the scalar results may differ by one unit from
//!       simd ones which are system dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/average.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::average[mask](x, ...)` provides a masked
//!     version of `average` which is
//!     equivalent to `if_else(mask, average(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/average.cpp}
//!
//!   * eve::raw
//!
//!     when `raw(average)(x, args, ...)` is used, no provision is made to avoid
//!     overflows for more than 2 parameters.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/raw/average.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(average_, average);
}

#include <eve/module/core/regular/impl/average.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/average.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/average.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/average.hpp>
#endif
