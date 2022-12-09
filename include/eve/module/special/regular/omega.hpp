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
//! @addtogroup special
//! @{
//!   @var omega
//!   @brief Computes the the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log
//!   x+x\f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_ordered_value T >
//!      T omega(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the Wright \f$\omega\f$ function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/omega.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(omega_, omega);
}

#include <eve/module/special/regular/impl/omega.hpp>
