//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>

namespace eve
{
template<typename Options>
struct acos_t : elementwise_callable<acos_t, Options, raw_option>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(acos_t, acos_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acos
//!   @brief `elementwise_callable` object computing the arc cosine.
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
//!      // Regular overloads
//!      constexpr auto acos(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto acos[raw](floating_value auto x)                     noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto acos[conditional_expr auto c](floating_value auto x) noexcept; // 3
//!      constexpr auto acos[logical_value auto m](floating_value auto x)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//!      input in the range \f$[0 , \pi]\f$.
//!      In particular:
//!      * If `x` is \f$1\f$, \f$+0\f$ is returned.
//!      * If \f$|x| > 1\f$, `NaN` is returned.
//!      * If `x` is a `NaN`, `NaN` is returned.
//!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near `x = 1`
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: acos](https://en.cppreference.com/w/cpp/numeric/math/acos)
//!   *  [Wolfram MathWorld: Inverse Cosine](https://mathworld.wolfram.com/InverseCosine.html)
//!   *  [DLMF: Error Functions](https://dlmf.nist.gov/4.23)
//!   *  [Wikipedia: Arc cosinus](https://fr.wikipedia.org/wiki/Arc_cosinus)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acos.cpp}
//================================================================================================
  inline constexpr auto acos = functor<acos_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acos_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(raw))
      {
        auto tmp  = pio_2(eve::as(a0))
          + (ieee_constant<0x1.1a62633145c07p-54, -0x1.777a5c0p-25f>(eve::as<T>{}) - asin(a0));
        return if_else(a0 == T(1), eve::zero, tmp);
      }
      else
      {
        if constexpr( simd_value<T> )
        {
          auto const half  = eve::half(eve::as(a0));
          auto const mhalf = eve::mhalf(eve::as(a0));

          auto x           = eve::abs(a0);
          auto x_larger_05 = x > half;

          x = if_else(x_larger_05, eve::sqrt(fma(mhalf, x, half)), a0);
          x = asin(x);
          x = add[x_larger_05](x, x);
          x = eve::if_else((a0 < mhalf), eve::pi(eve::as(a0)) - x, x);

          return eve::if_else(x_larger_05, x, eve::pio_2(eve::as(a0)) - x);
        }
        else if constexpr( scalar_value<T> )
        {
          if( a0 == T(1) )          return T(0);
          if( eve::abs(a0) > T(1) ) return nan(eve::as<T>());

          if constexpr( std::same_as<T, float> )
          {
            if( a0 < -0.5f )      return pi(eve::as<T>()) - 2.0f * eve::asin(eve::sqrt(inc(a0) * 0.5f));
            else if( a0 > 0.5f )  return 2.0f * eve::asin(eve::sqrt(oneminus(a0) * 0.5f));
            else                  return pio_2(eve::as<T>()) - eve::asin(a0);
          }
          else if constexpr( std::same_as<T, double> )
          {
            if( a0 > 0.5 ) return 2.0 * eve::asin(eve::sqrt(fma(-0.5, a0, 0.5)));

            T const pio4 = pio_4(eve::as<T>());

            T z = pio4 - eve::asin(a0);
            z += T(0x1.1a62633145c07p-55); // Pio_4lo(as<T>());
            z += pio4;

            return z;
          }
        }
      }
    }
  }
}
