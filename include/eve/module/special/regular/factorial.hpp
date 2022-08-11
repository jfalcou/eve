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
//!   @var factorial
//!   @brief Computes \f$\displaystyle n! = \prod_{i=1}^n i\f$.
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
//!      template< eve::value N >
//!      eve::as_floating_point_value<N> factorial(N x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!   **Return value**
//!
//!  The value of \f$ n!\f$ is returned.
//!
//!  @warning
//!    This function will overflow as soon as the input is greater than 171 for integral or double
//!    entries and if the entry is greater than 34 for float.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/factorial.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(factorial_, factorial);
}

#include <eve/module/special/regular/impl/factorial.hpp>
