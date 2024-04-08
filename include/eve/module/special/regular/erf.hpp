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
  struct erf_t : elementwise_callable<erf_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erf_t, erf_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erf
//!   @brief Computes the error function: \f$ \displaystyle
//!   \mbox{erf}(x)=\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$.
//!
//!   **Defined in header**
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
//!      template< eve::floating_ordered_value T >
//!      T erf(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!    **Return value**
//!
//!    The value of the error function is returned. In particular:
//!
//!      * If the argument is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the argument is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!      * If the argument is Nan, nan returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erf.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto erf = functor<erf_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    T
    erf_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr( eve::platform::supports_invalids )
          if( is_nan(a0) ) return a0;
        if constexpr( eve::platform::supports_infinites )
          if( eve::is_infinite(a0) ) return signnz(a0);
        if constexpr( std::is_same_v<T, double> )
        {
          T y = eve::abs(a0);
          if( y <= 0.46875 ) // 15/32
          {
            T ysq = if_else(y > epso_2(as<T>()), sqr(y), eve::zero);
            return kernel1_erf1(a0, ysq);
          }
          else
          {
            if( a0 > 26.543 ) return sign(a0);
            else if( y <= 4 )
            {
              T res = kernel1_erf2(a0, y);
              res   = kernel1_finalize2(res, y);
              res   = (half(as<T>()) - res) + half(as<T>());
              if( is_ltz(a0) ) res = -res;
              return res;
            }
            else // if  (y <= 26.543)
            {
              T res = kernel1_erf3(a0, y);
              res   = kernel1_finalize2(res, y);
              res   = (half(as<T>()) - res) + half(as<T>());
              if( is_ltz(a0) ) res = -res;
              return res;
            }
          }
        }
        else if constexpr( std::is_same_v<T, float> )
        {
          T x = eve::abs(a0);
          if( x < 6.6666667e-01f ) // 2/3
          {
            return a0 * kernel_erf1(sqr(x));
          }
          else
          {
            T z  = x / inc(x) - 0.4f; // Ratio<T, 2, 5>();
            T r2 = oneminus(exp(-sqr(x)) * kernel_erfc2(z));
            if( is_ltz(a0) ) r2 = -r2;
            return r2;
          }
        }
      }
      else //simd case
      {
        using elt_t = element_type_t<T>;
        if constexpr( std::is_same_v<elt_t, double> )
        {
          T y        = eve::abs(a0);
          y          = if_else(y > T(26.543), T(26.543), y);
          T    sqry  = eve::sqr(y);
          auto test1 = eve::is_less(y, T(0.46875)); // 15/32;
          T    r1    = eve::zero(as<T>());
          auto nb    = eve::count_true(test1);
          if( nb > 0 ) // here y < 0.46875
          {
            T ysq = if_else(y > epso_2(as<T>()), sqry, eve::zero);
            r1    = kernel1_erf1(a0, ysq);
            if( nb == T::size() ) return r1;
          }
          auto test2 = (y <= T(4));
          auto test3 = logical_andnot(test2, test1);

          auto nb1 = eve::count_true(test3);
          if( nb1 > 0 ) // here we treat 0.46875 <= y and y <= 4
          {
            T res = kernel1_erf2(a0, y);
            res   = kernel1_finalize2(res, y);
            res   = (half(as<T>()) - res) + half(as<T>());
            res   = minus[is_ltz(a0)](res);
            r1    = if_else(test3, res, r1);
            if( nb + nb1 == T::size() ) return r1;
          }
          // here we treat y > 4
          T res = kernel1_erf3(a0, y);
          res   = kernel1_finalize2(res, y);
          res   = (half(as<T>()) - res) + half(as<T>());
          res   = minus[is_ltz(a0)](res);
          r1    = if_else(test2, r1, res);
          return r1;
        }
        else if constexpr( std::is_same_v<elt_t, float> )
        {
          T    x     = eve::abs(a0);
          T    r1    = eve::zero(as<T>());
          auto test1 = eve::is_less(x, 6.6666667e-01f); // Ratio<T, 2, 3>());
          auto nb    = eve::count_true(test1);
          if( nb > 0 )
          {
            r1 = a0 * kernel_erf1(sqr(x));
            if( nb >= T::size() ) return r1;
          }
          T z = x / inc(x);
          z -= T(0.4);
          T r2 = oneminus(exp(-sqr(x)) * kernel_erfc2(z));
          r2   = minus[is_ltz(a0)](r2);
          r1   = if_else(test1, r1, r2);
          if constexpr( eve::platform::supports_infinites )
            r1 = eve::if_else(eve::is_infinite(a0), eve::sign(a0), r1);
          return r1;
        }
      }
    }
  }
}
