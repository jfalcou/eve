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
#include <eve/module/math.hpp>
#include <eve/module/special/detail/erf_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct erfc_t : elementwise_callable<erfc_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erfc_t, erfc_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erfc
//!   @brief `elementwise_callable` object computing the complementary error function
//!    \f$ \displaystyle
//!    \mbox{erf}(x)=1-\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$
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
//!      constexpr auto erfc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto erfc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto erfc[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the complementary error function: \f$ \displaystyle
//!        \mbox{erf}(x)=1-\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$.
//!        In particular:
//!          * If the argument is \f$\pm0\f$, \f$1\f$ is returned.
//!          * If the argument is \f$\infty\f$, \f$1\f$ is returned.
//!          * If the argument is \f$-\infty\f$,\f$2\f$ is returned.
//!          * If the argument is Nan, nan is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: erfc](https://en.cppreference.com/w/cpp/numeric/math/erfc)
//!   *  [Wolfram MathWorld: Erfc](https://mathworld.wolfram.com/Erfc.html)
//!   *  [DLMF](https://dlmf.nist.gov/7.2#i)
//!   *  [Wikipedia: Error Function](https://en.wikipedia.org/wiki/Error_function)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/erf.cpp}
//================================================================================================
  inline constexpr auto erfc = functor<erfc_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T,  callable_options O >
    constexpr T erfc_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr( eve::platform::supports_invalids )
          if( is_nan(x) ) return x;
        if constexpr( eve::platform::supports_infinites )
          if( eve::is_infinite(x) ) return oneminus(signnz(x));
        if( is_eqz(x) ) return T(1);
        if constexpr( std::is_same_v<T, double> )
        {
          T y = eve::abs(x);
          if( y <= 0.46875 ) // 15/32
          {
            T ysq = if_else(y > epso_2(as<T>()), sqr(y), eve::zero);
            T res = kernel1_erf1(x, ysq);
            res   = oneminus(res);
            return res;
          }
          else if( y <= 4.0 )
          {
            T res = kernel1_erf2(x, y);
            res   = kernel1_finalize2(res, y);
            if( is_ltz(x) ) res = 2.0 - res;
            return res;
          }
          else if( y <= 26.543 )
          {
            T res = kernel1_erf3(x, y);
            res   = kernel1_finalize2(res, y);
            if( is_ltz(x) ) res = T(2) - res;
            return res;
          }
          else return (is_ltz(x)) ? T(2) : zero(as<T>());
        }
        else if constexpr( std::is_same_v<T, float> )
        {
          T xx = eve::abs(x);
          T r1 = zero(as<T>());
          T z  = xx / inc(xx);
          if( 3.0f * xx < 2.0f ) { r1 = kernel_erfc3(z); }
          else
          {
            z -= 0.4f;
            r1 = exp(-sqr(xx)) * kernel_erfc2(z);
          }
          return (x < 0.0f) ? 2.0f - r1 : r1;
        }
      }
      else //simd case
      {
        auto a0 = x;
        using elt_t = element_type_t<T>;
        if constexpr( std::is_same_v<elt_t, double> )
        {
          T y        = eve::abs(a0);
          y          = if_else(y > T(26.543), T(27), y);
          T    sqry  = sqr(y);
          auto test1 = eve::is_less(y, T(0.46875)); // 15/32;
          T    r1    = eve::zero(as<T>());
          auto nb    = eve::count_true(test1);
          if( nb > 0 ) // here y < 0.46875
          {
            T ysq = if_else(y > epso_2(as<T>()), sqry, eve::zero);
            r1    = kernel1_erf1(a0, ysq);
            r1    = oneminus(r1);
            if( nb == T::size() ) return r1;
          }
          auto test2 = (y <= T(4));
          auto test3 = logical_andnot(test2, test1);

          auto nb1 = eve::count_true(test3);
          if( nb1 > 0 ) // here we treat 0.46875 <= y and y <= 4
          {
            T res = kernel1_erf2(a0, y);
            res   = kernel1_finalize2(res, y);
            res   = if_else(is_ltz(a0), 2.0 - res, res);
            r1    = if_else(test3, res, r1);
            if( nb + nb1 == T::size() ) return r1;
          }
          // here we treat y > 4
          T res = kernel1_erf3(a0, y);
          res   = kernel1_finalize2(res, y);
          res   = if_else(is_ltz(a0), 2.0 - res, res);
          r1    = if_else(test2, r1, res);
          return r1;
        }
        else if constexpr( std::is_same_v<elt_t, float> )
        {
          T    xv     = eve::abs(a0);
          auto test0 = eve::is_ltz(a0);
          T    r1    = zero(as<T>());
          auto test1 = eve::is_less(xv, 6.6666667e-01f);
          T    z     = xv / inc(xv);

          auto nb = eve::count_true(test1);
          if( nb > 0 )
          {
            r1 = kernel_erfc3(z);
            if( nb >= T::size() ) return eve::if_else(test0, T(2) - r1, r1);
          }
          z -= T(0.4);
          T r2 = exp(-sqr(x)) * kernel_erfc2(z);
          r1   = if_else(test1, r1, r2);
          if constexpr( eve::platform::supports_infinites ) r1 = if_else(xv == inf(as<T>()), zero, r1);

          return eve::if_else(test0, T(2) - r1, r1);
        }
      }
    }
  }
}
