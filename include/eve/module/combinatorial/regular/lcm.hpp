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
#include <eve/module/combinatorial/regular/gcd.hpp>
#include <eve/module/core.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/as_element.hpp>
#include <numeric>

namespace eve
{
  template<typename Options>
  struct lcm_t : elementwise_callable<lcm_t, Options>
  {
    template<eve::value T, eve::value U>
    requires (same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE
    common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(lcm_t, lcm_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var lcm
//!   @brief `elementwise_callable` object computing the least common multiple of the inputs.
//!
//!   @groupheader{Callable Signatures}
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
//!      template <integral_value T0, integral_value T1> constexpr common_value_t<T0, T1> lcm(T0 p, T1 n) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto lcm[conditional_expr auto c](integral_value auto p, integral_value auto n)        noexcept; // 2
//!      constexpr auto lcm[logical_value auto m](integral_value auto p, integral_value auto n)           noexcept; // 2
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
//!      1. Returns the least common multiple of |p| and |n|.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor)
//!   *  [C++ standard reference: gcd](https://en.cppreference.com/w/cpp/numeric/gcd)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/combinatorial/lcm.cpp}
//================================================================================================
  inline constexpr auto lcm = functor<lcm_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T lcm_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      a = eve::abs(a);
      b = eve::abs(b);
      if constexpr( integral_scalar_value<T>)
      {
        return std::lcm(a, b);
      }
      else if constexpr( scalar_value<T> )
      {
        if( !b || !a ) return T(0);
        else return b / gcd(a, b) * a;
      }
      else
      {
        return a * (b / gcd(a, if_else(is_nez(b), b, eve::one)));
      }
    }
  }
}
