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
  struct atan2d_t : elementwise_callable<atan2d_t, Options, pedantic_option>
  {
    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(atan2d_t, atan2d_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var atan2d
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
//!      constexpr auto atan2d(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto atan2d[pedantic](floating_value auto x, floating_value auto y)                noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto atan2d[conditional_expr auto c][floating_value auto x, floating_value auto y) noexcept; // 3
//!      constexpr auto atan2d[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating values](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!    1. The arc tangent in degrees of \f$\frac{y}x\f$  in the range \f$[-180 , +180]\f$, is returned.
//!       The **IEEE** limiting values are almost all satisfied :
//!
//!       *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
//!       *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm180\f$ is returned
//!       *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm90\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-90\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+90\f$  is returned
//!       *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+180\f$ is returned
//!       *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-180\f$ is returned
//!       *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!       *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!       *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!       The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!       not **IEEE** conformant, but allows to simplify (and
//!       speed) the implementation. In all other cases, the result is standard conformant.
//!    2. Same as 1, except that all **IEEE** limiting values are satisfied :
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$,\f$\pm135\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm45\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-90\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+90\f$  is returned
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/atan2d.cpp}
//================================================================================================
  inline constexpr auto atan2d = functor<atan2d_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    atan2d_(EVE_REQUIRES(cpu_), O const& o, T const& a0, const U a1) noexcept
    {
      return radindeg(atan2[o](a0, a1));
    }
  }
}
