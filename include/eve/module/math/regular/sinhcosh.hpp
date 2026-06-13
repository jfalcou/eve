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
  struct sinhcosh_t : elementwise_callable< sinhcosh_t, Options, pedantic_option, raw_option, fast_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

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
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
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

  namespace _
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto sinhcosh_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      using elt_t =  element_type_t<T>;
      constexpr elt_t ovflimit = maxlog(as<elt_t>());
      constexpr elt_t hlf =  eve::half(as<elt_t>());
      auto x = eve::abs(a0);

      if constexpr( scalar_value<T> )
      {
        if( x < T(0x1.0p-28) ) return eve::zip(a0, one(eve::as<T>()));
        auto h = copysign(T(1), a0);
        if( x >= ovflimit )
        {
          auto w = exp[o](x * hlf);
          auto t = hlf * w;
          t *= w;
          return eve::zip(t * h, t);
        }
        h *= hlf;
        auto t    = expm1(x);
        auto inct = inc(t);
        auto u    = t / inct;
        auto s    = h * (fnma(t, u, t) + t);
        auto c    = (x > elt_t(22)) ? inct *hlf: average(inct, rec[pedantic](inct));
        return eve::zip(s, c);
      }
      else
      {
        auto h    = if_else(is_positive(a0), one(eve::as<T>()), mone(eve::as<T>()));
        auto t    = expm1(x);
        auto inct = inc(t);
        auto u    = t / inct;
        auto z    = fnma(t, u, t);
        auto s    =hlf* h * (z + t);
        auto invt = if_else(x > elt_t(22), eve::zero, rec[pedantic](inct));
        auto c    = average(inct, invt);
        auto test = x < ovflimit;
        if( eve::all(test) ) return eve::zip(s, c);

        auto w = exp[o](x * hlf);
        t      = hlf* w;
        t *= w;

        s = if_else(test, s, t * h);
        c = if_else(test, c, t);
        return eve::zip(s, c);
      }
    }
  }
}
