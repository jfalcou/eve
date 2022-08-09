//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countl_one
//!   @brief Computes the number of consecutive 1 in a value starting from left.
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
//!      T countl_one(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 1 ("one") bits in the value of `x`, starting
//!      from the most significant bit ("left"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/countl_one.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(countl_one_, countl_one);
}

#include <eve/module/core/regular/impl/countl_one.hpp>
