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

namespace eve
{
  template<typename Options>
  struct lcm_t : elementwise_callable<lcm_t, Options>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
      requires (same_lanes_or_scalar<T, U>)
    {
      return this->behavior(as<common_value_t<T, U>>{}, eve::current_api, this->options(), v, w);
    }

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
  //!      template <value T0, value T1> constexpr common_value_t<T0, T1> lcm(T0 p, T1 n) noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto lcm[conditional_expr auto c](value auto p, value auto n)        noexcept; // 2
  //!      constexpr auto lcm[logical_value auto m](value auto p, value auto n)           noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `p`, `n`: [values](@ref value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!    **Return value**
  //!
  //!      1. Returns the least common multiple of |p| and |n|.
  //!      2. [The operation is performed conditionnaly](@ref conditional)
  //!
  //!    @warning  `p` and `n` can be of any [values](@ref eve::value) type, but when the types are not
  //!      integral the least common multiple is defined only if `p` and `n` elements are
  //!      [flint](@ref eve::is_flint). If any of the arguments is not flint the result is undefined.
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
    template<callable_options O, typename T>
    constexpr T lcm_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      EVE_ASSERT(eve::all(is_flint(a) && is_flint(b)), "eve::lcm: some entries are not flint");
      a = eve::abs(a);
      b = eve::abs(b);

      if constexpr (scalar_value<T>)
      {
        if( !b || !a ) return T(0);
        else return b / gcd(a, b) * a;
      }
      else return a * (b / gcd(a, if_else(b, b, eve::one)));
    }
  }
}
