//==================================================================================================
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
//! @addtogroup special
//! @{
//!   @var erf_inv
//!   @brief Computes the inverse of the error function.
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
//!      template< eve::floating_real_value T >
//!      T erf_inv(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value `y` such that `erf(y)==x` is returned. For `x` outside of \f$[-1,1]\f$, the result
//!   is NaN.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erf_inv.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(erf_inv_, erf_inv);
}

#include <eve/module/special/regular/impl/erf_inv.hpp>
