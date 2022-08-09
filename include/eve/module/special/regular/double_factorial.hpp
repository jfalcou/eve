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
//!   @var double_factorial
//!   @brief Computes the double factorial of `n`
//!
//!   THe double factorial is defined as \f$\displaystyle (2n)!! =
//!   \prod_{i=1}^n (2i)\f$ and \f$\displaystyle (2n+1)!! = \prod_{i=0}^n (2i+1)\f$
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
//!      template< eve::unsigned_value N >
//!      eve::as_double_as<N, double> double_factorial(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!   **Return value**
//!
//!   The value of the double factorial of `n` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/double_factorial.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(double_factorial_, double_factorial);
}

#include <eve/module/special/regular/impl/double_factorial.hpp>
