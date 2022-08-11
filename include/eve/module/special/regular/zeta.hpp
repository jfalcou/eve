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
//!   @var zeta
//!   @brief Computes the Riemann \f$\zeta\f$ function.
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
//!      T zeta(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the Riemann function defined as
//!   \f$\displaystyle \zeta(s)=\sum_{n=0}^\infty \frac1{n^s}\f$  is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/zeta.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(zeta_, zeta);
}

#include <eve/module/special/regular/impl/zeta.hpp>
