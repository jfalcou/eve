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
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct atan2_t : elementwise_callable<atan2_t, Options, pedantic_option>
  {
    template<floating_value T, floating_value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
    requires (same_lanes_or_scalar<T, U>)
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T, U>), v, w);
    }

    EVE_CALLABLE_OBJECT(atan2_t, atan2_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var atan2
//!   @brief `elementwise_callable` object computing the arc tangent using the
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
//!      constexpr auto atan2(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto atan2[pedantic](floating_value auto x, floating_value auto y)                noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto atan2[conditional_expr auto c][floating_value auto x, floating_value auto y) noexcept; // 3
//!      constexpr auto atan2[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 3
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
//!    1. The arc tangent of \f$\frac{y}x\f$  in the range \f$[-\pi , +\pi]\f$ radians, is returned.
//!       The **IEEE** limiting values are almost all satisfied :
//!
//!         *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard conforming)
//!         *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm\pi\f$ is returned
//!         *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!         *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm\frac\pi2\f$ is returned
//!         *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac\pi2\f$ is returned
//!         *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac\pi2\f$  is returned
//!         *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+\pi\f$ is returned
//!         *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-\pi\f$ is returned
//!         *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!         *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!         *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!    The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!    not **IEEE** conformant, but allows to simplify (and speed) the implementation.
//!    In all other cases, the result is standard conformant.
//!    2. Same as 1, except that all **IEEE** limiting values are satisfied :
//!      *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\pm\frac{3\pi}4\f$ is returned
//!      *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm\frac{\pi}4\f$ is returned
//!      *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac\pi2\f$ is returned
//!      *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac\pi2\f$  is returned
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference:atan2](https://en.cppreference.com/w/cpp/numeric/math/atan2)
//!   *  [Wolfram MathWorld: Inverse Tangent](https://mathworld.wolfram.com/InverseTangent.html)
//!   *  [Wikipedia: Atan2](https://en.wikipedia.org/wiki/Atan2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/atan2.cpp}
//================================================================================================
  inline constexpr auto atan2 = functor<atan2_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    atan2_(EVE_REQUIRES(cpu_), O const&, T const& a0, const U a1) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t a00(a0);
      r_t a10(a1);
      if constexpr(O::contains(pedantic))
      {
        if constexpr(scalar_value<r_t> && platform::supports_nans)
        {
          if (is_unordered(a00, a10)) return nan(eve::as(a00));
        }
        if constexpr(platform::supports_infinites)
        {
          auto test1 =  eve::is_infinite(a00) && eve::is_infinite(a10);
          a00 =  eve::if_else(test1, eve::copysign(one(eve::as(a00)), a00), a00);
          a10 =  eve::if_else(test1, eve::copysign(one(eve::as(a00)), a10), a10);
        }

        r_t q = eve::abs(a00/a10);
        r_t z = atan_kernel(q, rec[pedantic](q));
        r_t sgn = signnz(a00);
        if constexpr(scalar_value<r_t>)
        {
          z = (is_positive(a10)? z: pi(eve::as<r_t>())-z)*sgn;
          return is_eqz(a00) ? if_else(is_negative(a10), pi(eve::as(a00))*sgn, eve::zero) : z;
        }
        else
        {
          z = eve::if_else(eve::is_positive(a10), z, eve::pi(eve::as(a0))-z)*sgn;
          z = eve::if_else( eve::is_eqz(a00),
                            eve::if_else( eve::is_negative(a10),  eve::pi(eve::as(a00))*sgn, eve::zero),
                            z);
          if constexpr(platform::supports_nans)
            return  eve::if_else( is_unordered(a00, a10), eve::allbits, z);
          else
            return z;
        }
      }
      else
      {
        auto q = eve::abs(a00/a10);
        auto z = detail::atan_kernel(q, eve::rec[pedantic](q));
        return if_else(is_positive(a10), z, (pi(eve::as(a00)) - z))*signnz(a00);
      }
    }
  }
}
