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
//! @addtogroup core_reduction
//! @{
//!   @var all
//!   @brief Computes a bool value which is true if and only if all elements of `x` are not zero.
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
//!      bool all(eve::as_logical<T> x) noexcept;  //1
//!
//!      template< eve::top_bits M >
//!      bool all(M m) noexcept;                   //2
//!   }
//!   @endcode
//!
//!   1. A bool value which is true if and only if all elements of `x` are not zero.
//!   2  A bool value which is true if and only if all top bits elements of `x` are not zero.
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::logical_value).
//!     * `m` :  [argument](@ref eve::top_bits).
//!
//!    **Return value**
//!
//!    A bool value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/all.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::all[mask](x)` provides a masked
//!     version of `all` which is
//!     equivalent to : all not masked elements are not zero.
//!
//!      **Example**
//!
//! @godbolt{doc/core/masked/all.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif
