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
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct sinhcosh_t : elementwise_callable<sinhcosh_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE kumi::tuple<T, T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

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
//!   **Defined in Header**
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
//!      template< eve::floating_value T >
//!      kumi::tuple<T, T> sinhcosh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//!   }
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) pair of values containing the
//! hyperbolic sine and the hyperbolic cosine of the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinhcosh.cpp}
//!  @}
//================================================================================================
  inline constexpr auto sinhcosh = functor<sinhcosh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE kumi::tuple<T, T>
    sinhcosh_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr( has_native_abi_v<T> )
      {
        T    ovflimit = maxlog(as<T>());
        auto x        = eve::abs(a0);

        if constexpr( scalar_value<T> )
        {
          if( x < T(0x1.0p-28) ) return {a0, one(eve::as<T>())};
          auto h = (a0 > T(0)) ? T(1) : T(-1);
          if( x >= ovflimit )
          {
            auto w = exp(x * half(eve::as<T>()));
            auto t = half(eve::as<T>()) * w;
            t *= w;
            return {t * h, t};
          }
          h *= half(eve::as<T>());
          auto t    = expm1(x);
          auto inct = inc(t);
          auto u    = t / inct;
          auto s    = h * (fnma(t, u, t) + t);
          auto c    = (x > T(22.0f)) ? inct * half(eve::as<T>()) : average(inct, rec(inct));
          return {s, c};
        }
        else
        {
          auto h    = if_else(is_positive(a0), one(eve::as<T>()), mone(eve::as<T>()));
          auto t    = expm1(x);
          auto inct = inc(t);
          auto u    = t / inct;
          auto z    = fnma(t, u, t);
          auto s    = half(eve::as<T>()) * h * (z + t);
          auto invt = if_else(x > T(22.0f), eve::zero, rec(inct));
          auto c    = average(inct, invt);
          auto test = x < ovflimit;
          if( eve::all(test) ) return {s, c};

          auto w = exp(x * half(eve::as<T>()));
          t      = half(eve::as<T>()) * w;
          t *= w;

          s = if_else(test, s, t * h);
          c = if_else(test, c, t);
          return {s, c};
        }
      }
      else { return apply_over2(sinhcosh, a0); }
    }
  }
}
