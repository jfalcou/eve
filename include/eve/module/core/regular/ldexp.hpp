//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/is_flint.hpp>

namespace eve
{
template<typename Options>
struct ldexp_t : strict_elementwise_callable<ldexp_t, Options, pedantic_option>
{
  template<eve::floating_value T, eve::value U>
  requires(eve::same_lanes_or_scalar<T, U>)
  constexpr EVE_FORCEINLINE as_wide_as_t<T,U> operator()(T x, U n) const
  {
    return this->behavior(as<as_wide_as_t<T,U>>{}, eve::current_api, this->options(), x, n);
  }

  EVE_CALLABLE_OBJECT(ldexp_t, ldexp_);
};
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ldexp
//!   @brief `strict_elementwise callable` computing \f$\textstyle x 2^n\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto ldexp(floating_value auto x, integral_value N)                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ldexp[conditional_expr auto c](floating_value auto x), integral_value N) noexcept; // 2
//!      constexpr auto ldexp[logical_value auto m](floating_value auto x, integral_value N)     noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto abs[pedantic](floating_value auto x, integral_value N)                   noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `n`: [integral value argument](@ref eve::integral_value).
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!     1. The value of \f$\textstyle x 2^n\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. Takes extra care to handling limit values.
//!         * If `x` is \f$\pm0\f$, it is returned, unmodified.
//!         * If `x` is \f$\pm\infty\f$, it is returned, unmodified.
//!         * If `n` is 0, then `x` is returned, unmodified.
//!         * If `x` is NaN, NaN is returned.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/ldexp)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/ldexp.cpp}
//================================================================================================
  inline constexpr auto ldexp = functor<ldexp_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/ldexp.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ldexp.hpp>
#endif
