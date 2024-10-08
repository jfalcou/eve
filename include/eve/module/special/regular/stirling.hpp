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
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct stirling_t : elementwise_callable<stirling_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(stirling_t, stirling_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var stirling
  //!   @brief `elementwise_callable` object computing the Stirling approximation of the \f$\Gamma\f$ function.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/special.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto stirling(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto stirling[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto stirling[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`: [floating value](@ref floating_value).
  //!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!      * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of an approximation of the \f$\Gamma\f$ function by \f$\displaystyle \Gamma(x) \approx \sqrt{2 \pi} x^{x-\frac12}
  //!        e^{-x} \left( 1 + \frac1{x} P(\frac1{x})\right)\f$, where \f$P\f$ is a polynomial,
  //!        is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Stirling approximation](https://en.wikipedia.org/wiki/Stirling%27s_approximation)
  //!   *  [Wolfram MathWorld: Stirling's Approximation](https://mathworld.wolfram.com/StirlingsApproximation.html)
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/special/stirling.cpp}
  //================================================================================================
  inline constexpr auto stirling = functor<stirling_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr T stirling_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      using elt_t = element_type_t<T>;
      auto stirling1 = [](const T& xx){
        if constexpr( std::is_same_v<elt_t, float> )
        {
          return
          eve::reverse_horner(xx, T(0x1.555556p-4f), T(0x1.c71c72p-9f)
                             , T(-0x1.5f7260p-9f), T(-0x1.e166b2p-13f))
          ;
        }
        else if constexpr( std::is_same_v<elt_t, double> )
        {
          return
          eve::reverse_horner(xx, T(0x1.5555555555986p-4), T(0x1.c71c71b98c5fdp-9), T(-0x1.5f72607d44fd7p-9)
                             , T(-0x1.e166b27e61d7cp-13), T(0x1.9cc72592d7293p-11))
          ;
        }
      };
      const T Stirlingsplitlim = ieee_constant<0x1.ac51ec0p+4f, 0x1.1e083ba3443d4p+7>(eve::as<T>{});
      const T Stirlinglargelim = ieee_constant<0x1.1851e60p+5f, 0x1.5800000000000p+7>(eve::as<T>{});
      const T Sqrt_2pi = ieee_constant<0x1.40d9320p+1f, 0x1.40d931ff62704p+1>(eve::as<T>{});
      if constexpr( simd_value<T> )
      {
        a0        = if_else(is_gez(a0), a0, eve::allbits);
        T w       = rec[pedantic](a0);
        w         = fma(w, stirling1(w), one(eve::as<T>()));
        T    y    = exp(-a0);
        auto test = is_less(a0, Stirlingsplitlim);
        T    z    = a0 - half(eve::as<T>());
        z         = if_else(test, z, half(eve::as<T>()) * z);
        T v       = pow_abs(a0, z);
        y *= v;
        y = if_else(test, y, y * v); /* Avoid overflow in pow() */
        y *= Sqrt_2pi * w;
        y = if_else(a0 == inf(eve::as<T>()), a0, y);
        return if_else(a0 > Stirlinglargelim, inf(eve::as<T>()), y);
      }
      else if constexpr( scalar_value<T> )
      {
        if( is_ltz(a0) ) return nan(eve::as<T>());
        if( is_nan(a0) ) return a0;
        if( a0 > Stirlinglargelim ) return inf(eve::as<T>());
        T w = rec[pedantic](a0);
        w   = fma(w, stirling1(w), one(eve::as<T>()));
        T y = exp(-a0);
        if( is_eqz(y) ) return inf(eve::as<T>());
        T z = a0 - half(eve::as<T>());
        if( a0 >= Stirlingsplitlim )
        { /* Avoid overflow in pow() */
          const T v = pow_abs(a0, z * half(eve::as<T>()));
          y *= v;
          y *= v;
        }
        else
        {
          y *= pow_abs(a0, z);
        }
        y *= Sqrt_2pi * w;
        return y;
      }
    }
  }
}
