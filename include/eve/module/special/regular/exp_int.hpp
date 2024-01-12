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
struct exp_int_t : elementwise_callable<exp_int_t, Options, saturated_option>
{
  template<eve::floating_ordered_value T, eve::ordered_value I>
  EVE_FORCEINLINE  eve::as_wide_as_t<T, I>  operator()(I n, T v) const noexcept { return EVE_DISPATCH_CALL(n, v); }

  template<eve::floating_ordered_value T>
  EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(exp_int_t, exp_int_);
};

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
//!      template< eve::floating_ordered_value T >
//!      T exp_int(T x) noexcept;
//!
//!      template< eve::unsigned_value N, eve::floating_ordered_value T >
//!      T exp_int(N n, T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value). If not present taken to be 1.
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
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
inline constexpr auto exp_int = functor<exp_int_t>;
}


#include <eve/module/special/regular/impl/exp_int.hpp>
