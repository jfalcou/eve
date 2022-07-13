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
//!   @var lbeta
//!   @brief Computes the natural logarithm of the beta function.
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
//!      T lbeta(T x) noexcept;
//!
//!      template< eve::floating_real_value T, eve::floating_real_value U >
//!      eve:common_compatible_value<T,U>  lbeta(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [strictly positive real floating argument](@ref eve::floating_real_value).
//!
//!     * `y` :  [strictly positive real floating argument](@ref eve::floating_real_value).
//!
//!    **Return value**
//!
//!    the value of the  logarithm of the beta function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/lbeta.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lbeta_, lbeta);
}

#include <eve/module/special/regular/impl/lbeta.hpp>
