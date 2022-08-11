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
//! @addtogroup combinatorial
//! @{
//!   @var gcd
//!   @brief Computes the greatest common divisor of the inputs.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::real_value T,  eve::real_value U >
//!      T gcd(T p, U n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `p`, `n`: [Real values](@ref eve::value).
//!
//!    **Return value**
//!
//!    If both p and n are zero, returns zero. Otherwise, returns the greatest common divisor of |p|
//!    and |n|.
//!
//!    @warning
//!    `p` and `n` can be of any [real values](@ref eve::value) type, but when the types are not
//!    integral the greatest common divisor is defined only if `p` and `n` elements are [flint](@ref
//!    eve::is_flint). If any of the arguments is not flint the result is undefined.
//!
//!   **Example**
//!
//!     @godbolt{doc/combinatorial/regular/gcd.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct gcd_;
}

EVE_MAKE_CALLABLE(gcd_, gcd);
}

#include <eve/module/combinatorial/regular/impl/gcd.hpp>
