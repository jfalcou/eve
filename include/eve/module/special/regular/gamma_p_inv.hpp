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
//!   @var gamma_p_inv
//!   @brief Computes the inverse of the normalized lower incomplete \f$\Gamma\f$ function.
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
//!      template< eve::floating_real_value T, eve::floating_real_value U >
//!      eve:common_compatible_value<T,U>  gamma_p_inv(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [real floating arguments](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!  The value of the  inverse of the normalized lower incomplete \f$\Gamma\f$ function
//!  relative to the first parameter is returned as  :
//!  \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/gamma_p.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(gamma_p_inv_, gamma_p_inv);
}

#include <eve/module/special/regular/impl/gamma_p_inv.hpp>
