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
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/logical_and.hpp>


namespace eve
{
  template<typename Options>
  struct logical_notor_t : strict_elementwise_callable<logical_notor_t, Options>
  {
    template<logical_value T, logical_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE  auto operator()(T a, U b) const noexcept -> decltype(logical_and(a, b))
    requires(eve::same_lanes_or_scalar<T, U>)
    { return this->behavior(as<decltype(logical_and(a, b))>{}, eve::current_api, this->options(), a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE T operator()(T a, bool b) const noexcept
    { return this->behavior(as<T>{}, eve::current_api, this->options(), a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE T operator()(bool a, T b) const noexcept
    { return this->behavior(as<T>{}, eve::current_api, this->options(), a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const noexcept
    { return this->behavior(as<bool>{}, eve::current_api, this->options(), a, b); }

    EVE_CALLABLE_OBJECT(logical_notor_t, logical_notor_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_notor
//!   @brief Computes the logical NOTOR of its arguments.
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
//!      constexpr auto logical_notor(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical NOTOR of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_notor(x, y)` is semantically equivalent to `!x || y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_notor.cpp}
//================================================================================================
  inline constexpr auto logical_notor = functor<logical_notor_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE constexpr auto logical_notor_(EVE_REQUIRES(cpu_),
                                                  O const & ,
                                                  T a, U b) noexcept
    {
      using r_t = decltype(logical_and(a, b));
      if constexpr( scalar_value<T> || scalar_value<U> ) return r_t(!a || b);
      else return !a || b;
    }

    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr
    auto logical_notor_(EVE_REQUIRES(cpu_), O const & , T a, bool b) noexcept
    {
      return b ? true_(as(a)) : !a;
    }

    template<typename U, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_notor_(EVE_REQUIRES(cpu_), O const & , bool a, U b) noexcept
    {
      return a ? b : true_(as(b));
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_notor_(EVE_REQUIRES(cpu_), O const & , bool a, bool b) noexcept
    {
      return !a || b;
    }
  }
}
