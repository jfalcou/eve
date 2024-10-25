/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/rempio2_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct rempio2_t : elementwise_callable < rempio2_t, Options
                                          , quarter_circle_option, half_circle_option
                                          , full_circle_option, medium_option, big_option
                                          >
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE
    zipped<T,T,T> operator()(T v) const  noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(rempio2_t, rempio2_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var rempio2
//!
//! @brief `elementwise_callable` object computing the remainder of the division by \f$\pi/2\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!   {
//!      // Regular overload
//!      constexpr auto rempio2(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto rempio2[quarter_circle](floating_value auto x)          noexcept; // 2.a
//!      constexpr auto rempio2[half_circle](floating_value auto x)             noexcept; // 2.b
//!      constexpr auto rempio2[full_circle](floating_value auto x)             noexcept; // 2.c
//!      constexpr auto rempio2[medium](floating_value auto x)                  noexcept; // 2.d
//!      constexpr auto rempio2[big](floating_value auto x)                     noexcept; // 2.e
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. A tuple-like consisting of an [flint](@ref eve::is_flint) value designing the quadrant and two
//!       floating values of type `T` giving the remainder of `x` modulo \f$\pi/2\f$ and a corrective
//!       to the rounding error on the first result.
//!    2. These options enable faster computations by assuming that the input satisfies the following respective condition:
//!         1. \f$|x| \le \pi/4\f$
//!         2. \f$|x| \le \pi/2\f$
//!         3. \f$|x| \le \pi\f$
//!         4. \f$|x| \le 10^4\f$
//!         5. no conditions,  will directly use the most expansive reduction algorithm
//!
//!       For each option, if the respective above conditon is not met the result is undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/rempio2.cpp}
//================================================================================================
  inline constexpr auto rempio2 = functor<rempio2_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    rempio2_(EVE_REQUIRES(cpu_), O const&, T const& x) noexcept
    {
      if      constexpr( O::contains(quarter_circle))  return rempio2_half_circle(x);
      else if constexpr( O::contains(half_circle))     return rempio2_half_circle(x);
      else if constexpr( O::contains(full_circle))     return rempio2_full_circle(x);
      else if constexpr( O::contains(medium))          return rempio2_medium(x);
      else if constexpr( O::contains(big))             return rempio2_big(x);
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(x))))   return eve::zip(T(0), x, T(0));
        else if( eve::all(x <= Rempio2_limit[half_circle](as(x)))) return rempio2_half_circle(x);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(x)))) return rempio2_full_circle(x);
        else if( eve::all(x <= Rempio2_limit[medium](as(x))))      return rempio2_medium(x);
        else                                                        return rempio2_big(x);
      }
    }
  }
}
