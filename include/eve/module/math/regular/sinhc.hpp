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
#include <eve/module/math/regular/sinh.hpp>
#include <eve/module/math/regular/exp.hpp>

namespace eve
{
  template<typename Options>
  struct sinhc_t : elementwise_callable<sinhc_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinhc_t, sinhc_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var sinhc
//!
//! @brief Callable object computing \f$\frac{e^x-e^{-x}}{2x}\f$.
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
//!      T sinhc(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input divided by the
//! input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinhc.cpp}
//!
//!  @}
//================================================================================================
 inline constexpr auto sinhc = functor<sinhc_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinhc_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return one(eve::as(a0));
        if constexpr( eve::platform::supports_infinites )
          if( is_infinite(a0) ) return zero(eve::as<T>());
        if constexpr( eve::platform::supports_denormals )
          return eve::abs(a0) < eps(as<T>()) ? one(eve::as<T>()) : sinh(a0) / a0;
        else return sinh(a0) / a0;
      }
      else
      {
        auto sinhc_kernel = [](auto x2){
          using elt_t = element_type_t<T>;
          if constexpr( std::is_same_v<elt_t, float> )
          {
            return
              eve::reverse_horner(x2, T(0x1.000000p+0f), T(0x1.555598p-3f)
                                 , T(0x1.10f77cp-7f), T(0x1.ab3c5ep-13f))
              ;
          }
          else
          {
            return inc(x2 * eve::reverse_horner(x2, T(-0x1.5782bdbf6ab05p+18), T(-0x1.694b8c71d6182p+13)
                                               , T(-0x1.4773a398ff4fep+7), T(-0x1.9435fe8bb3cd6p-1))
                       /
                       eve::reverse_horner(x2, T(-0x1.01a20e4f90044p+21), T(0x1.1a7ba7ed72245p+15)
                                          , T(-0x1.15b6096e96484p+8), T(0x1.0p0))
                      );
          }
        };

        T    x   = abs(a0);
        auto lt1 = is_less(x, one(eve::as<T>()));
        auto nb  = eve::count_true(lt1);
        T    z   = zero(eve::as<T>());
        if( nb > 0 )
        {
          z = sinhc_kernel(sqr(x));
          if( nb >= T::size() ) return z;
        }
        auto test1 = is_greater(x, maxlog(eve::as<T>()) - log_2(eve::as<T>()));
        T    fac   = if_else(test1, half(eve::as<T>()), one(eve::as<T>()));
        T    tmp   = exp(x * fac);
        T    tmp1  = (half(eve::as<T>()) * tmp) / x;
        T    r     = if_else(test1, tmp1 * tmp, average(tmp, -rec[pedantic2](tmp)) / x);
        if constexpr( eve::platform::supports_infinites ) r = if_else(x == inf(eve::as<T>()), x, r);
        return if_else(lt1, z, r);
      }
    }
  }
}
