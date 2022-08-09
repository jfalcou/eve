//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
//!   @var hi
//!   @brief Computes the most significant half of each lane.
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
//!      auto hi(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes the [elementwise](@ref glossary_elementwise) higher
//!        significant half of the  value bits,
//!        returning each element as an unsigned integer of half the size of the input element.
//!
//!    @note
//!      If you also need the lower part `lohi` is more efficient.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/hi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(hi_, hi);
}

#include <eve/module/core/regular/impl/hi.hpp>
