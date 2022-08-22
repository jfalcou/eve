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
//! @addtogroup core_arithmetic
//! @{
//!   @var dist
//!   @brief Computes the distance of its arguments.
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
//!      eve::common_compatible_t<T, U> dist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :   [real](@ref eve::value) or [complex](@ref eve::complex) arguments.
//!
//!    **Return value**
//!
//!    The value of the distance of the arguments is returned,  i.e. `eve::abs (x-y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/dist.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::saturated
//!
//!     The call `saturated(dist)(x, y)` computes a saturated distance.
//!     Contrary to the non decorated case, it guarantees
//!     that the result is always defined. If \f$|x-y|\f$ is not representable
//!     [the greatest representable positive value](@ref eve::valmax) is returned.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/dist.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(dist_, dist);
}

#include <eve/module/core/regular/impl/dist.hpp>
