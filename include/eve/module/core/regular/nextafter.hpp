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
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/prev.hpp>

#
namespace eve
{
  template<typename Options>
  struct nextafter_t : elementwise_callable<nextafter_t, Options, pedantic_option>
  {
    template<eve::value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T t, U u) const noexcept
    { return EVE_DISPATCH_CALL(t, u); }

    EVE_CALLABLE_OBJECT(nextafter_t, nextafter_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var nextafter
//!   @brief `elementwise_callable` object computing the next representable element  element in
//!    the second parameter direction.
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
//!      // Regular overloads
//!      constexpr auto nextafter(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto nextafter[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto nextafter[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto nextafter[pedantic](/* any of the above overloads */)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. the next representable value after  `x` in the `y` direction is returned.
//!         If `y == x` returns `x`.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!      3. Provides a version of `nextafter` for which floating plus zero and minus zero are distinct.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/nextafter.cpp}
//================================================================================================
  inline constexpr auto nextafter = functor<nextafter_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    nextafter_(EVE_REQUIRES(cpu_), O const& o, T const& a, T const & b) noexcept
    {
      if constexpr( scalar_value<T> )
        return (a < b) ? next[o](a) : ((a > b) ? prev[o](a) : a);
      else if constexpr( simd_value<T> )
      {
        if constexpr(O::contains(pedantic))
        {
          return if_else(a < b, next[o](a), if_else(a > b, prev[o](a), a));
        }
        else
        {
          return next[a < b](prev[a > b](a));
        }
      }
    }
  }
}
