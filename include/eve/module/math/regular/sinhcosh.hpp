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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct sinhcosh_t : elementwise_callable< sinhcosh_t, Options
                                          , quarter_circle_option, half_circle_option, full_circle_option
                                          , medium_option, big_option
                                          >
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const
    {
      return this->behavior(as<zipped<T,T>>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sinhcosh_t, sinhcosh_);
  };

  //================================================================================================
  //! @addtogroup math_hyper
  //! @{
  //! @var sinhcosh
  //!
  //! @brief Callable object performing the simultaneous computations of
  //! the hyperbolic sine and cosine.
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
  //!      // Regular overload
  //!      constexpr auto sinhcosh(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto sinhcosh[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto sinhcosh[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!      * `x`: [floating value](@ref floating_value).
  //!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!      * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   }
  //!
  //! **Return value**
  //!
  //!   1 .The computation returns a tuple-like whose elements are `sinh(x)` and `cosh(x)`
  //!   2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/sinhcosh.cpp}
  //================================================================================================
  inline constexpr auto sinhcosh = functor<sinhcosh_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE auto sinhcosh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      T    ovflimit = maxlog(as<T>());
      auto x        = eve::abs(a0);

      if constexpr( scalar_value<T> )
      {
        if( x < T(0x1.0p-28) ) return eve::zip(a0, one(eve::as<T>()));
        auto h = (a0 > T(0)) ? T(1) : T(-1);
        if( x >= ovflimit )
        {
          auto w = exp(x * half(eve::as<T>()));
          auto t = half(eve::as<T>()) * w;
          t *= w;
          return eve::zip(t * h, t);
        }
        h *= half(eve::as<T>());
        auto t    = expm1(x);
        auto inct = inc(t);
        auto u    = t / inct;
        auto s    = h * (fnma(t, u, t) + t);
        auto c    = (x > T(22.0f)) ? inct * half(eve::as<T>()) : average(inct, rec[pedantic](inct));
        return eve::zip(s, c);
      }
      else
      {
        auto h    = if_else(is_positive(a0), one(eve::as<T>()), mone(eve::as<T>()));
        auto t    = expm1(x);
        auto inct = inc(t);
        auto u    = t / inct;
        auto z    = fnma(t, u, t);
        auto s    = half(eve::as<T>()) * h * (z + t);
        auto invt = if_else(x > T(22.0f), eve::zero, rec[pedantic](inct));
        auto c    = average(inct, invt);
        auto test = x < ovflimit;
        if( eve::all(test) ) return eve::zip(s, c);

        auto w = exp(x * half(eve::as<T>()));
        t      = half(eve::as<T>()) * w;
        t *= w;

        s = if_else(test, s, t * h);
        c = if_else(test, c, t);
        return eve::zip(s, c);
      }
    }
  }
}
