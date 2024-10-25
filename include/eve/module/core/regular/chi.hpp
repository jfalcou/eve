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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/forward.hpp>

namespace eve
{

  template<typename Options>
  struct chi_t : callable<chi_t, Options, conditional_option>
  {
    template<value T, value U, value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V>
    operator()(T a, U lo, V hi) const noexcept
    {
      EVE_ASSERT(eve::all(lo <= hi), "[eve::chi] bounds are not correctly ordered");
      return EVE_DISPATCH_CALL(a, lo, hi);
    }

    template<value T,  typename  B>
    constexpr EVE_FORCEINLINE T
    operator()(T a, B const & belongs) const noexcept
    {
      return EVE_DISPATCH_CALL(a, belongs);
    }

    EVE_CALLABLE_OBJECT(chi_t, chi_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var chi
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
//!      constexpr auto chi(value auto x, value auto lo,  value auto hi)             noexcept; // 1
//!      constexpr auto chi(value auto x, auto belongs)                              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto chi[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
//!      constexpr auto chi[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: value to chi.
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) of the interval.
//!     * `belongs`: predicate function
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!        1. Each [element](@ref glossary_elementwise)  of the result contains:
//!           * `0`, if `x` is less than `lo`. or if `hi` is strictly less than `x`.
//!           * `1` otherwise.
//!        2  1 in the type of x if belongs(x) evaluate to true else 0.
//!        3. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note If any `lo` is not less or equal to the corresponding `hi` the routine asserts.
//!
//!  @groupheader{External references}
//!   *  [wikipedia](https://en.wikipedia.org/wiki/Indicator_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/chi.cpp}
//================================================================================================
  inline constexpr auto chi = functor<chi_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T0, typename T1,  typename T2, callable_options O>
    EVE_FORCEINLINE constexpr auto chi_(EVE_REQUIRES(cpu_), O const & c, T0 a, T1 l, T2 h) noexcept
    {
      using r_t =  common_value_t<T0, T1, T2>;
      auto z = if_else( r_t(a) < r_t(h) && r_t(a) >= r_t(l), one(as<r_t>()), zero);
      if constexpr(O::contains(eve::condition_key))
        return mask_op(c[eve::condition_key], return_2nd, a, z);
      else
        return z;
    }

    template<typename T, typename B, callable_options O>
    EVE_FORCEINLINE constexpr auto chi_(EVE_REQUIRES(cpu_), O const & c, T x, B const & b) noexcept
    {
     auto z = if_else(b(x), one(as(x)), zero);
     if constexpr(O::contains(eve::condition_key))
       return  mask_op(c[eve::condition_key], return_2nd, x, z);
     else
       return z;
    }
  }
}
