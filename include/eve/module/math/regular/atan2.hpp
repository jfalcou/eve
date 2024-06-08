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
    template<eve::floating_ordered_value T, eve::floating_ordered_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(atan2_t, atan2_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var atan2
//!
//! @brief Callable object computing the arc tangent using the
//! signs of arguments to determine the correct quadrant.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T eve::floating_value U>
//!      auto atan2(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real values](@ref eve::value)
//!
//! **Return value**
//!
//! the arc tangent of \f$\frac{y}x\f$  in the range \f$[-\pi , +\pi]\f$ radians, is returned.
//! The **IEEE** limiting values are almost all satisfied :
//!
//!   *  If `x` and `y` are both zero or infinites, Nan is returned (this is not standard
//!      conforming)
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly negative or \f$-0\f$, \f$\pm\pi\f$ is returned
//!   *  If `y` is \f$\pm0\f$ and `x` is strictly positive or \f$+0\f$, \f$\pm0\f$ is returned
//!   *  If `y` is \f$\pm\infty\f$ and `x` is finite, \f$\pm\frac\pi2\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly negative, \f$-\frac\pi2\f$ is returned
//!   *  If `x` is \f$\pm0\f$ and `y` is strictly positive, \f$+\frac\pi2\f$  is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and positive, \f$+\pi\f$ is returned
//!   *  If `x` is \f$-\infty\f$ and `y` is finite and negative, \f$-\pi\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and positive, \f$+0\f$ is returned
//!   *  If `x` is \f$+\infty\f$ and `y` is finite and negative, \f$-0\f$ is returned
//!   *  If either `x` is Nan or `y` is Nan, Nan is returned
//!
//!    The call will return a NaN if `x` and `y` are both either null or infinite: this result is
//!    not **IEEE** conformant, but allows to simplify (and
//!    speed) the implementation. In all other cases, the result is standard conformant.
//!
//!    The result type is the [common value type](@ref common_value_t) of the two parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/atan2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::pedantic
//!
//!     The call `pedantic(atan2)(`x`,`y`)` returns the same results as the regular call, but all
//!      **IEEE** limiting values are satisfied :
//!
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$-\infty\f$, \f$\pm\frac{3\pi}4\f$ is returned
//!       *  If `y` is \f$\pm\infty\f$ and `x` is \f$+\infty\f$, \f$\pm\frac{\pi}4\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm-0\f$, \f$-\frac\pi2\f$ is returned
//!       *  If `x` is \f$\pm0\f$ and `y` is \f$\pm+0\f$, \f$+\frac\pi2\f$  is returned
//!  @}
//================================================================================================
  inline constexpr auto atan2 = functor<atan2_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    constexpr EVE_FORCEINLINE common_value_t<T, U>
    atan2_(EVE_REQUIRES(cpu_), O const&, T const& a0, const U a1) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t a00(a0);
      r_t a10(a1);
      if constexpr(O::contains(pedantic2))
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
        r_t z = atan_kernel(q, rec[pedantic2](q));
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
        auto z = detail::atan_kernel(q, eve::rec[pedantic2](q));
        return if_else(is_positive(a10), z, (pi(eve::as(a00)) - z))*signnz(a00);
      }
    }
  }
}
