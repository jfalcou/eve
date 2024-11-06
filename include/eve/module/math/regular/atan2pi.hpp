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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/atan2.hpp>

namespace eve
{
  template<typename Options>
  struct atan2pi_t : elementwise_callable<atan2pi_t, Options, pedantic_option>
  {
    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(atan2pi_t, atan2pi_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var atan2pi
//!   @brief `elementwise_callable` object computing the arc tangent in degrees using the
//!   signs of the arguments to determine the correct quadrant.
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
//!      constexpr auto atan2pi(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto atan2pi[pedantic](floating_value auto x, floating_value auto y)                noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto atan2pi[conditional_expr auto c][floating_value auto x, floating_value auto y) noexcept; // 3
//!      constexpr auto atan2pi[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`, `y`: [floating values](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    1. the arc tangent of \f$\frac{y}x\f$  in \f$\pi\f$, in the range [-1, +1], is returned.
//!       The **IEEE** limiting values are almost all satisfied :
//!
//!       *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
//!       *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm1\f$ is returned
//!       *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm\frac12\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac12\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac12\f$  is returned
//!       *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+1\f$ is returned
//!       *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-1\f$ is returned
//!       *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!       *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!       *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!       The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!       not **IEEE** conformant, but  allows to simplify (and
//!       speed) the implementation. In all other cases, the result is standard conformant.
//!    2. Same as 1, except that all **IEEE** limiting values are satisfied :
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\pm\frac34\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm\frac14\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac12\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac12\f$  is returned
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference:atan2](https://en.cppreference.com/w/cpp/numeric/math/atan2)
//!   *  [Wolfram MathWorld: Inverse Tangent](https://mathworld.wolfram.com/InverseTangent.html)
//!   *  [Wikipedia: Atan2](https://en.wikipedia.org/wiki/Atan2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/atan2pi.cpp}
//================================================================================================
  inline constexpr auto atan2pi = functor<atan2pi_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    atan2pi_(EVE_REQUIRES(cpu_), O const& o, T const& a0, const U a1) noexcept
    {
      return radinpi(atan2[o](a0, a1));
    }
  }
}
