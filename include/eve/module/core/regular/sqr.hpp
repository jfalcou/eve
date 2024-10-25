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
#include <eve/module/core/constant/sqrtvalmax.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>


namespace eve
{
template<typename Options>
struct sqr_t : elementwise_callable<sqr_t, Options, saturated_option, lower_option, upper_option>
{
  template<eve::value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqr_t, sqr_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sqr
//!   @brief Computes the square of the parameter.
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
//!      constexpr auto sqr(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sqr[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto sqr[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sqr[saturated](value auto x)               noexcept; // 3
//!      constexpr auto sqr[lower](value auto x)                   noexcept; // 4
//!      constexpr auto sqr[upper](value auto x)                   noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!     1. value containing the [elementwise](@ref glossary_elementwise)
//!        square of `x` if it is representable in this type.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3.  Contrary to the  non-decorated case, it guarantees
//!      that the result is [elementwise](@ref glossary_elementwise) greater or equal than 0. More
//!      specifically, for any integer value `x`, the call evaluates to:
//!      [`valmax(as(x))`](@ref valmax) as soon as `abs[saturated](x)`
//!      is greater than `sqrtvalmax(as(x))`.
//!     4. The square is done in a 'round toward \f$-\infty\f$ mode. The product is guaranted
//!       to be less or equal to the exact one.
//!     5. The square is done in a 'round toward \f$\infty\f$ mode. The product is guaranted
//!       to be greater or equal to the exact one.
//!
//!  @note
//!      For  [integral signed values](@ref eve::value)   if `eve::abs[eve::saturated](x)`
//!      is greater than `eve::Sqrtvalmax(as(x))` the corresponding element result
//!      is undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sqr.cpp}
//================================================================================================
  inline constexpr auto sqr = functor<sqr_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  { 

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    sqr_(EVE_REQUIRES(cpu_), O const &o, T const &a0) noexcept
    {
      if constexpr(O::contains(saturated))
      {
        if constexpr( scalar_value<T> )
        {
          return (eve::abs[saturated](a0) > sqrtvalmax(eve::as(a0))) ? valmax(eve::as(a0)) : sqr(a0);
        }
        else
        {
          return if_else(eve::abs[saturated](a0) > sqrtvalmax(eve::as(a0)), valmax(eve::as(a0)), sqr(a0));
        }
      }
      else
        return mul[o](a0, a0);
    }
  }
}
 
