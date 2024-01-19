//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct gcd_t : elementwise_callable<gcd_t, Options, raw_option>
{
  template<eve::ordered_value T, ordered_value U>
  constexpr EVE_FORCEINLINE common_value_t<T, U>
  operator()(T v, U w) const noexcept { return EVE_DISPATCH_CALL(v, w); }

  EVE_CALLABLE_OBJECT(gcd_t, gcd_);
};

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
//!      template< eve::ordered_value T,  eve::ordered_value U >
//!      constexpr common_value_t<T, U> gcd(T p, U n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `p`, `n`: [ordered values](@ref eve::value).
//!
//!    **Return value**
//!
//!    If both p and n are zero, returns zero. Otherwise, returns the greatest common divisor of |p|
//!    and |n|.
//!
//!    @warning
//!    `p` and `n` can be of any [ordered values](@ref eve::value) type, but when the types are not
//!    integral the greatest common divisor is defined only if `p` and `n` elements are [flint](@ref
//!    eve::is_flint). If any of the arguments is not flint the result is undefined.
//!
//!   **Example**
//!
//!     @godbolt{doc/combinatorial/regular/gcd.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto gcd = functor<gcd_t>;

}

#include <eve/module/combinatorial/regular/impl/gcd.hpp>
