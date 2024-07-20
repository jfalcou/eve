//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct logical_and_t : strict_elementwise_callable<logical_and_t, Options>
  {
    template<logical_value T, logical_value U>
    constexpr EVE_FORCEINLINE auto operator()(T a, U b) const noexcept -> decltype(a && b)
    requires(eve::same_lanes_or_scalar<T, U>)
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value U>
    constexpr EVE_FORCEINLINE U  operator()(bool a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE T  operator()(T a, bool b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(logical_and_t, logical_and_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_and
//!   @brief `strict_elementwise_callable` computing the logical AND of its arguments.
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
//!      constexpr auto logical_and(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical AND of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_and(x, y)` is semantically equivalent to `x && y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
//!
//!    @note
//!      Although the infix notation with `&&` is supported, the `&&` operator on
//!      standard scalar types is the original one and so will return bool instead of
//!      eve::logical_value.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/logical_and.cpp}
//! @}
//================================================================================================
  inline constexpr auto logical_and = functor<logical_and_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    logical_and_(EVE_REQUIRES(cpu_), O const &, T a, U b) noexcept
    {
      using r_t = as_logical_t<decltype(a && b)>;
      if constexpr( scalar_value<T> && scalar_value<U> ) return r_t(a && b);
      else return a && b;
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_and_(EVE_REQUIRES(cpu_), O const &, T a, bool b) noexcept
    {
      return b ? T {a} : false_(as<T>());
    }

    template<typename U, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_and_(EVE_REQUIRES(cpu_), O const &, bool a, U b) noexcept
    {
      return a ? U {b} : false_(as<U>());
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_and_(EVE_REQUIRES(cpu_), O const &, bool a, bool b) noexcept
    { return a && b; }
  }
}
