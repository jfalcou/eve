/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var lohi
//!   @brief Computes the the lohi pair of values.
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
//!      auto lohi(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes the [elementwise](@ref glossary_elementwise) the lower and higher parts of
//!        the input values, as a pair of unsigned integers
//!
//!      * The call lohi(x) is_semantically equivalent to [eve::lo(x), eve::hi(x)]
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/lo.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lohi_, lohi);
}

#include <eve/module/core/regular/impl/lohi.hpp>
