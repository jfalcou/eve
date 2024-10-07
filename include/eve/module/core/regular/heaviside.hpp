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
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/forward.hpp>

namespace eve
{

  template<typename Options>
  struct heaviside_t : elementwise_callable<heaviside_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T
    operator()(T a) const noexcept
    {
      return EVE_DISPATCH_CALL(a);
    }

    template<value T, value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    operator()(T a, U s) const noexcept
    {
      return EVE_DISPATCH_CALL(a, s);
    }

    EVE_CALLABLE_OBJECT(heaviside_t, heaviside_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var heaviside
//!   @brief `callable` indicatrix of the interval \f$[lo, hi[\f$ or of the set for which the invocable returns true.
//!
//!   **Defined in Header**
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
//!      constexpr auto heaviside(value auto x)                                            noexcept; // 1
//!      constexpr auto heaviside(value auto x, auto s)                                    noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto heaviside[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
//!      constexpr auto heaviside[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: value.
//!     * `s`: shift.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!        1. Each [element](@ref glossary_elementwise)  of the result contains:
//!           * `0`, if `x` is less  zero.
//!           * `1` otherwise.
//!        2. Each [element](@ref glossary_elementwise)  of the result contains:
//!           * `0`, if `x` is less than `s` (default to zero).
//!           * `1` otherwise.
//!        3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [wikipedia](https://en.wikipedia.org/wiki/Indicator_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/heaviside.cpp}
//! @}
//================================================================================================
  inline constexpr auto heaviside = functor<heaviside_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto heaviside_(EVE_REQUIRES(cpu_), O const & c, T a) noexcept
    {
      if constexpr(scalar_value<T>)
        return a > 0;
      else
        return bit_and(one(as(a)), is_gtz(a));
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto heaviside_(EVE_REQUIRES(cpu_), O const & c, T a, T s) noexcept
    {
      if constexpr(scalar_value<T>)
        return a > s;
      else
        return  bit_and(one(as(a)), a > s);
    }
  }
}
