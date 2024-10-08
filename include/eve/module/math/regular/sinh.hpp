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
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>

namespace eve
{
  template<typename Options>
  struct sinh_t : elementwise_callable<sinh_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sinh_t, sinh_);
  };

  //================================================================================================
  //! @addtogroup math_hyper
  //! @{
  //! @var sinh
  //!
  //! @brief `elementwise_callable` object computing \f$\frac{e^x-e^{-x}}2\f$.
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
  //!      constexpr auto sinh(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto sinh[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto sinh[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!      * `x`: [floating value](@ref floating_value).
  //!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!      * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input.
  //!       In particular:
  //!        * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!        * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
  //!        * If the element is a `NaN`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/sinh.cpp}
  //================================================================================================
  inline constexpr auto sinh = functor<sinh_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T sinh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return a0;
      }
      T x = eve::abs(a0);

      if constexpr( scalar_value<T> )
      {
        T h = (a0 > T(0)) ? T(1) : T(-1);
        if( x >= maxlog(as<T>()) )
        {
          T w = exp(x * half(eve::as<T>()));
          T t = half(eve::as<T>()) * w;
          t *= w;
          return t * h;
        }
        h *= half(eve::as<T>());
        T t    = expm1(x);
        T inct = inc(t);
        T u    = t / inct;
        T s    = h * (fnma(t, u, t) + t);
        return s;
      }
      else
      {
        auto h    = if_else(is_gtz(a0), one(eve::as<T>()), mone);
        auto t    = expm1(x);
        auto inct = inc(t);
        auto u    = t / inct;
        auto z    = fnma(t, u, t);
        auto s    = half(eve::as<T>()) * h * (z + t);

        s         = if_else(is_eqz(a0), a0, s);
        auto test = x < maxlog(as<T>());
        if( eve::all(test) ) return s;
        auto w = exp(x * half(eve::as<T>()));
        t      = half(eve::as<T>()) * w;
        t *= w;

        return if_else(test, s, t * h);
      }
    }
  }
}
