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
//!   @var exp_int
//!   @brief Computes the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$.
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
//!      template< eve::unsigned_value N, eve::floating_real_value T >
//!      T exp_int(N n, T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the exponential integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/exp_int.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(exp_int_, exp_int);
}

#include <eve/module/special/regular/impl/exp_int.hpp>
