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
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>


namespace eve
{
  template<typename Options>
  struct logical_or_t : strict_elementwise_callable<logical_or_t, Options>
  {
    template<logical_value T, logical_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE auto operator()(T a, U b) const noexcept -> as_logical_t<decltype(a && b)>
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value U>
    constexpr EVE_FORCEINLINE auto  operator()(bool a, U b) const noexcept -> as_logical_t<decltype(U(a) && b)>
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE auto  operator()(T a, bool b) const noexcept -> as_logical_t<decltype(a && T(b))>
    { return EVE_DISPATCH_CALL(a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(logical_or_t, logical_or_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_or
//!   @brief Computes the logical OR of its arguments.
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
//!      constexpr auto logical_or(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical_ rguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical OR of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_or(x, y)` is semantically equivalent to `x || y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
//!
//!    @note
//!      Although the infix notation with `||` is supported, the `||` operator on
//!      standard scalar types is the original one and so will return bool instead of
//!      eve::logical_value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_or.cpp}
//================================================================================================
  inline constexpr auto logical_or = functor<logical_or_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    logical_or_(EVE_REQUIRES(cpu_), O const &, T a, U b) noexcept
    {
      using r_t = as_logical_t<decltype(a || b)>;
      if constexpr( scalar_value<T> && scalar_value<U> ) return r_t(a || b);
      else return a || b;
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_or_(EVE_REQUIRES(cpu_), O const & , T a, bool b) noexcept
    {
      return b ? true_(as<T>()) : T {a};
    }

    template<typename U, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_or_(EVE_REQUIRES(cpu_), O const & , bool a, U b) noexcept
    {
      return a ? true_(as<U>()) : U {b};
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_or_(EVE_REQUIRES(cpu_), O const & , bool a, bool b) noexcept
    { return a || b; }
  }
}
