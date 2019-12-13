//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_MEDIUM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_MEDIUM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>  
#include <eve/function/nearest.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/max.hpp>
#include <type_traits>
#include <cstdlib>

namespace eve::detail
{

  // x < 281474976710656 (2.81476710656e+14)
  template<typename N, typename ABI>
  EVE_FORCEINLINE auto reduce_medium_(EVE_SUPPORTS(cpu_), wide<double, N, ABI> const &x) noexcept
  {
    static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
    static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
    static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
    static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */
    
    auto xn =  nearest(x*Twoopi<double>());
    auto xn1 = (xn + 8.0e22) - 8.0e22;
    auto xn2 = xn - xn1;
    auto y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x)))); 
    auto n = quadrant(xn); 
    auto da = xn1 * pp3;
    auto t = y - da;
    da = (y - t) - da;
    da = fma(xn, pp4, fnma(xn2, pp3, da));
    auto a = t + da;
    da = (t - a) + da;   
    return std::make_tuple(n, a, da); 
  }
  
  /* float use   x < 0x1.7d4998p+38 (4.09404e+11) */
  template<typename N, typename ABI>
  EVE_FORCEINLINE auto  reduce_medium_(EVE_SUPPORTS(cpu_)
                                      , wide<float, N, ABI> const &xx) noexcept
  {
    using t_t = wide<float, N, ABI>; 
    static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
    static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
    static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
    static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */
    auto x  = convert(xx, double_); 
    auto xn =  nearest(x*Twoopi<double>());
    auto xn1 = (xn + 8.0e22) - 8.0e22;
    auto xn2 = xn - xn1;
    auto y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x)))); 
    auto n = convert(quadrant(xn), single_); //  int4 n = v.i[LOW_HALF] & 3;
    auto da = xn1 * pp3;
    auto t = y - da;
    da = (y - t) - da;
    da = fma(xn, pp4, fnma(xn2, pp3, da));
    auto a = t + da;
    da = (t - a) + da;
    auto fa = convert(a, single_);
    auto dfa = convert((a-convert(fa, double_))+da, single_);
    if (any(eve::abs(fa) > Pio_4<float>()) )
    {
      t_t n1; 
      std::tie(n1, fa, dfa) =eve::reduce_fast(fa);
      n =quadrant(n+n1); 
      return std::make_tuple(n, fa, dfa); 
    }
    return std::make_tuple(n, fa, dfa); 
  }
  
}

#endif
