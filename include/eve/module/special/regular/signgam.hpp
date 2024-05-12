/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//!   @var signgam
//!   @brief Computes the sign of the \f$\Gamma\f$ function.
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
//!      T signgam(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of `eve::sign(eve::tgamma(x))` is returned (without computing `eve::tgamma(x)`);
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/signgam.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(signgam_, signgam);
}

#include <eve/module/special/regular/impl/signgam.hpp>
