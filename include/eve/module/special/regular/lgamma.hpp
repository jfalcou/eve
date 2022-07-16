//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!   @var lgamma
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
//!      template< eve::floating_real_value T >
//!      eve:common_compatible_value<T,U> lgamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the  logarithm of the absolute value of the \f$\Gamma\f$ function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lgamma.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lgamma_, lgamma);
}

#include <eve/module/special/regular/impl/lgamma.hpp>
