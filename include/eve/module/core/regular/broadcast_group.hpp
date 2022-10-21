//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

#include <bit>
#include <optional>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var broadcast_group
//!   @brief Computes the    TODO
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
//!      T broadcast_group(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of TODO
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  TODO
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(broadcast_group_, broadcast_group);
}

#include <eve/module/core/regular/impl/broadcast_group.hpp>
