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
//!   @var maximum
//!   @brief Computes the maximal value of an simd vector
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
//!      eve::element_type_t<T> maximum(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameter**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The scalar maximal value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/maximum.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::maximum[mask](x)` provides a masked
//!     version of `maximum` which is
//!     equivalent to : ``maximum(if_else(mask, x, valmin(as(x))))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/maximum.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(maximum_, maximum);
}

#include <eve/module/core/regular/impl/maximum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/maximum.hpp>
#endif
