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
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/hypot.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>

namespace eve
{
  template<typename Options>
  struct asinh_t : elementwise_callable<asinh_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(asinh_t, asinh_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var asinh
//!
//! @brief Callable object computing \f$\log(x+\sqrt{x^2+1})\f$.
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
//!      template< eve::floating_value T >
//!      T asinh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      The inverse hyperbolic sine is semantically equivalent to \f$\log(x+\sqrt{x^2+1})\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!      * for every z: eve::asinh(eve::conj(z)) == eve::conj(std::asinh(z))
//!      * for every z: eve::asinh(-z) == -eve::asinh(z)
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$+\infty+i \pi/2\f$
//!      * If z is \f$x,NaN\f$ (for any finite x), the result is \f$NaN+ iNaN\f$
//!      * If z is \f$+\infty+ iy\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$+\infty+ i\pi/4\f$
//!      * If z is \f$+\infty+ iNaN\f$, the result is \f$+\infty+ iNaN\f$
//!      * If z is \f$NaN+i 0\f$, the result is \f$NaN+i 0\f$
//!      * If z is \f$NaN+ iy\f$ (for any finite nonzero y), the result is \f$NaN+ iNaN\f$
//!      * If z is \f$NaN+i \infty\f$, the result is \f$\pm \infty+ iNaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$NaN+ iNaN\f$, the result is \f$NaN+ iNaN\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asinh.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto asinh = functor<asinh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T asinh_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      using vt_t = element_type_t<T>;
      T x        = eve::abs(a0);
      if constexpr( scalar_value<T> )
        if( x < sqrteps(eve::as<T>()) ) return a0; // scalar early return
      auto x_gt_oneosqrteps = x > oneosqrteps(eve::as<T>());
      auto bts              = bitofsign(a0);
      if constexpr( std::is_same_v<vt_t, double> )
      {
        if constexpr( scalar_value<T> ) // faster for great or small values
        {
          if( x_gt_oneosqrteps ) return bit_xor(log(x) + log_2(eve::as<T>()), bts);
          else if( x >= eve::half(eve::as<T>()) )
            return bit_xor(log(x + hypot(one(eve::as<T>()), x)), bts);
        }
        // remaining scalar case and all simd cases to avoid multiple computations as
        // this one is always ok
        T z = if_else(x_gt_oneosqrteps, dec(x), x + sqr(x) / eve::inc(hypot(one(eve::as<T>()), x)));
        if constexpr( eve::platform::supports_infinites ) z = if_else((x == inf(eve::as<T>())), x, z);
        z = add[x_gt_oneosqrteps](eve::log1p(z), log_2(eve::as<T>()));
        return bit_xor(z, bts);
      }
      else if constexpr( std::is_same_v<vt_t, float> )
      {
        auto        x_lt_half = x < half(eve::as<T>());
        T           x2        = sqr(x);
        T           z         = zero(eve::as<T>());
        std::size_t nb        = eve::count_true(x_lt_half);
        if( nb > 0 )
        {
          z = eve::reverse_horner(x2, T(0x1.000000p+0f), T(-0x1.55535ap-3f), T(0x1.329362p-4f)
                                 , T(-0x1.5dcb02p-5f), T(0x1.49adccp-6f))* x;
          if( nb >= cardinal_v<T> ) return bit_xor(z, bts);
        }
        auto case_1 = [](T const& x) { return x; };                                       // great x
        auto case_2 = [](T const& x) { return average(x, hypot(one(eve::as<T>()), x)); }; // lesser x
        auto tmp    = branch<scalar_value<T>>(x_gt_oneosqrteps, case_1, case_2)(x);
        auto z1     = bit_xor(if_else(x_lt_half, z, log(tmp) + log_2(eve::as<T>())), bts);
        if constexpr( eve::platform::supports_invalids )
          return if_else(is_nan(a0), eve::allbits, z1);
        else
          return z1;
      }
    }
  }
}
