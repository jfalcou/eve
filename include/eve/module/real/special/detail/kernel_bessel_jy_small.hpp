//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/function/converter.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of cylindrical bessel functions
// of the first kind and second kind for integer orders and small x values.
//
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

  ///////////////////////////////////////////////////////////////////////////////
  // small values routines
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  // Series summation utility
  ///////////////////////////////////////////////////////////////////////////////
  template <class F, class U, class V>
  EVE_FORCEINLINE auto sum_series( F& func
                         , U factor
                         , int max_terms
                         , V init_value) noexcept
  {
    using result_type =  typename F::result_type;

    int counter = max_terms;

    result_type result(init_value);
    result_type next_term;
    do{
      next_term = func();
      result += next_term;
    }
    while(eve::any(abs(factor * result) < eve::abs(next_term)) && --counter);

    // set max_terms to the actual number of terms of the series evaluated:
    max_terms = max_terms - counter;

    return result;
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Series evaluation for BesselJ(v, z) as z -> 0.
  // See http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01/0003/
  // Converges rapidly for all z << v.
  ///////////////////////////////////////////////////////////////////////////////

  template <class T> struct bessel_j_small_z_series_term
  {
    typedef T result_type;

    bessel_j_small_z_series_term(T v_, T x)
      : N(0), v(v_)
    {
      mult = x / 2;
      mult *= -mult;
      term = 1;
    }
    T operator()()
    {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
    }
  private:
    unsigned N;
    T v;
    T mult;
    T term;
  };


  template <class T>
  EVE_FORCEINLINE T bessel_j_small_z_series(T v, T x) noexcept
  {
    T prefix;
    using elt_t = element_type_t<T>;
    auto max_factorial = (sizeof(elt_t) == 4 ? 34 : 170);
    auto test = v < max_factorial;
    prefix = if_else(test
                    , eve::pow(x*elt_t(0.5), v) / eve::tgamma(v+1)
                    , eve::exp(v * eve::log(x*elt_t(0.5)) - eve::lgamma(v+1))
                    );
    if(eve::all(is_eqz(prefix)))  return prefix;
    bessel_j_small_z_series_term<T> s(v, x);
    auto max_iter = 1000000;
    T result = sum_series(s, eps(as(x)), max_iter, zero(as(x)));
    return prefix * result;
  }
}
