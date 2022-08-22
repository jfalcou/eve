//==================================================================================================
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
//!   @var log_abs_gamma
//!   @brief Computes the natural logarithm of the absolute value of the \f$\Gamma\f$ function.
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
//!      template< eve::floating_value T >
//!      T log_abs_gamma(T x) noexcept;                     //1
//!
//!      template< eve::floating_value T >
//!      T log_abs_gamma(as_complex_t<T> T z) noexcept;     //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!     * `z` :  [complex argument ](@ref eve::complex).
//!
//!   **Return value**
//!
//!   In the two cases, the value of the  logarithm of the absolute value of the \f$\Gamma\f$ function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/log_abs_gamma.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(log_abs_gamma_, log_abs_gamma);
}

#include <eve/module/special/regular/impl/log_abs_gamma.hpp>
