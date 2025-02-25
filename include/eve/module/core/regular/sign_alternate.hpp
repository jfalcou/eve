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
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct sign_alternate_t : elementwise_callable<sign_alternate_t, Options, upward_option, downward_option,
                                        to_nearest_option, toward_zero_option>
  {
    template<eve::signed_value T>
    constexpr EVE_FORCEINLINE T operator()(T n) const noexcept
    {
      return EVE_DISPATCH_CALL(n);
    }

    EVE_CALLABLE_OBJECT(sign_alternate_t, sign_alternate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sign_alternate
//!   @brief Computes \f$(-1)^n\f$.
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
//!      constexpr auto sign_alternate(signed_value auto n)                          noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto sign_alternate[downward](signed_value auto n)                noexcept; // 2
//!      constexpr auto sign_alternate[upward](signed_value auto n)                  noexcept; // 2
//!      constexpr auto sign_alternate[to_nearest](signed_value auto n)              noexcept; // 2
//!      constexpr auto sign_alternate[toward_zero](signed_value auto n)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto sign_alternate[conditional_expr auto c](signed_value auto n) noexcept; // 3
//!      constexpr auto sign_alternate[logical_value auto m](signed_value auto n)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. [elementwise](@ref glossary_elementwise) \f$(-1)^\tilde n\f$ is returned,  where \f$\tilde n\f$ is the truncation of `n`.
//!      2. The chosen rounding option is applyied to `n` before computation, instead of truncation.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sign_alternate.cpp}
//================================================================================================
  inline constexpr auto sign_alternate = functor<sign_alternate_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sign_alternate_(EVE_REQUIRES(cpu_), O const & o, T const& n) noexcept
    {
      if constexpr(integral_value<T>)
        return if_else(is_odd(n), mone, one(as(n)));
      else if constexpr(O::contains_any(upward, downward, to_nearest, toward_zero))
        return if_else(is_odd(round[o](n)), mone, one(as(n)));
      else
        return if_else(is_odd(trunc(n)), mone, one(as(n)));
    }
  }
}
