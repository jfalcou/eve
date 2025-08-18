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
#include <eve/as_element.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <iostream>

namespace eve
{
template<typename Options>
struct bezout_t : callable<bezout_t, Options>
{
  template<eve::value T, value U>
  requires (same_lanes_or_scalar<T, U>)
  constexpr EVE_FORCEINLINE
  kumi::tuple<common_value_t<T, U>, common_value_t<T, U>, common_value_t<T, U>>  operator()(T v, U w) const noexcept
  { return EVE_DISPATCH_CALL(v, w); }

  EVE_CALLABLE_OBJECT(bezout_t, bezout_);
};

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var bezout
//!   @brief `elementwise_callable` object computing the greatest common divisor of the inputs.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      template <integral_value T0, integral_value T1> constexpr common_value_t<T0, T1> bezout(T0 p, T1 n) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bezout[conditional_expr auto c](integral_value auto p, integral_value auto n)        noexcept; // 2
//!      constexpr auto bezout[logical_value auto m](integral_value auto p, integral_value auto n)           noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `p`, `n`: [integral values](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. If both p and n are zero, returns zero. Otherwise, returns the greatest common divisor of |p|
//!         and |n|.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Least common multiple](https://en.wikipedia.org/wiki/Greatest_common_divisor)
//!   *  [C++ standard reference: lcm](https://en.cppreference.com/w/cpp/numeric/bezout)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/combinatorial/bezout.cpp}
//================================================================================================
  inline constexpr auto bezout = functor<bezout_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto bezout_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      T t(1);
      T nt(0);
      T r(a);
      T nr(b);
      auto neznr = eve::is_nez(nr);

      while (eve::any(neznr))
      {
        auto q =  div[neznr][eve::toward_zero][eve::left](if_else(neznr, nr, one), r);
        auto tmp0 = t-q*nt;
        t = if_else(neznr, nt, t);
        nt =if_else(neznr, tmp0, nt);
        auto tmp1 = r-q*nr;
        r = if_else(neznr,nr, r);
        nr = if_else(neznr,tmp1, nr);
        neznr = eve::is_nez(nr);
      }
      auto bez = eve::div[eve::toward_zero](r-t*a, b);
      return eve::zip(r, t, bez);
    }
  }
}
