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
//!   @var reldist
//!   @brief Computes the relative distance of its arguments.
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
//!      eve::common_value_t<T, U> reldist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :   [real](@ref eve::floating_value) arguments.
//!
//!    **Return value**
//!
//!    The value of the relative distance of the arguments is returned,  i.e. `eve::abs (x-y)/max(abs(x), abs(y), 1)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/reldist.cpp}
//!
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/reldist.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(reldist_, reldist);
}

#include <eve/module/core/regular/impl/reldist.hpp>
