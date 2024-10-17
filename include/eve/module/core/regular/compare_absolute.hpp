//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
  template<typename Options>
  struct compare_absolute_t : strict_elementwise_callable<compare_absolute_t, Options, saturated_option>
  {
    template<typename F, value T>
    constexpr EVE_FORCEINLINE logical<T>  operator()(T a, F f) const
    {
      return EVE_DISPATCH_CALL(a, f);
    }

    template<value T, value U, typename F>
    requires(eve::same_lanes_or_scalar<T, U>)
      constexpr EVE_FORCEINLINE common_logical_t<T, U>  operator()(T a, U b, F f) const
    {
      return EVE_DISPATCH_CALL(a, b, f);
    }

    EVE_CALLABLE_OBJECT(compare_absolute_t, compare_absolute_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var compare_absolute
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          greater  than the second one.
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
//!      constexpr auto compare_absolute(value auto x, auto f) noexcept;                                        // 1
//!      constexpr auto compare_absolute(value auto x, value auto y, auto f) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto compare_absolute[conditional_expr auto c](value auto x, value auto y, auto f) noexcept; // 2
//!      constexpr auto compare_absolute[logical_value auto m](value auto x, value auto y, auto f)    noexcept; // 2
//!      constexpr auto compare_absolute[conditional_expr auto c](value auto x, auto f)               noexcept; // 2
//!      constexpr auto compare_absolute[logical_value auto m](value auto x, auto f)                  noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto compare_absolute[saturated](value auto x, auto f)                             noexcept; // 3
//!      constexpr auto compare_absolute[saturated](value auto x, value auto y, auto f)               noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `f`: one or two parameter predicate according to `y` presence.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `eve::compare_absolute(x,y,f)`  is semantically  equivalent to `f(abs(x), abs(y))` and
//!         `eve::compare_absolute(x,f)` is semantically  equivalent to `f(abs(x))` and
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. the option is transfered to 'abs' in the call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/compare_absolute.cpp}
//================================================================================================
  inline constexpr auto compare_absolute = functor<compare_absolute_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/abs.hpp>

namespace eve::detail
{
  template<value T, typename F, callable_options O>
  EVE_FORCEINLINE constexpr logical<T>
  compare_absolute_(EVE_REQUIRES(cpu_), O const& o, T a, F f) noexcept
  {
    return f(eve::abs[o](a));
  }

  template<value T, value U, typename F, callable_options O>
  EVE_FORCEINLINE constexpr common_logical_t<T,U>
  compare_absolute_(EVE_REQUIRES(cpu_), O const& o, T a, U b, F f) noexcept
  {
    return f(eve::abs[o](a), abs[o](b));
  }
}

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/compare_absolute.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/compare_absolute.hpp>
#endif
