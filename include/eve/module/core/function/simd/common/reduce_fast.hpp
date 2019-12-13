//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_FAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_FAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/combine.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/function/convert.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // up to 255*pi/4 ~200
  template < typename N,  typename ABI>
  EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                    , wide < float, N, ABI> const &xx) noexcept
  {
    /* Reduce range of x to within PI/2 with abs (x) <  255*pi/4. */
    using t_t = wide < float, N, ABI>; 
    if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::reduce_fast, xx);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      auto  [lo, hi] = xx.slice();
      auto  [nhi, xhi, dxhi]   = reduce_fast(hi);
      auto  [nlo, xlo, dxlo]   = reduce_fast(lo);
      return std::make_tuple(eve::combine( nlo, nhi)
                                      , eve::combine( xlo, xhi)
                                      , eve::combine( dxlo, dxhi));
    }
    else
    {
      auto x =  convert(xx, double_); 
      auto n =  nearest(x*Twoopi<double>()); 
      auto dxr = fma(n, -Pio_2<double>(), x); 
      return std::make_tuple(quadrant(convert(n, single_)), convert(dxr, single_), t_t(0.0f)); 
    }
  }
  
  template < typename N,  typename ABI>
  EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                    , wide < double, N, ABI> const &x) noexcept
  {
    if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::reduce_fast, x);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      auto  [lo, hi] = x.slice();
      auto  [nhi, xhi, dxhi]   = reduce_fast(hi);
      auto  [nlo, xlo, dxlo]   = reduce_fast(lo);
      return std::make_tuple(eve::combine( nlo, nhi)
                                      , eve::combine( xlo, xhi)
                                      , eve::combine( dxlo, dxhi));
    }
    else
    {
      /* Reduce range of x to within PI/2 with abs (x) < 105414350. */
      static const double mp1 = -0x1.921FB58000000p0;   /*  -1.5707963407039642      */
      static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
      static const double mp3 = -0x1.CB3B399D747F2p-55; /* -4.9789962505147994e-17  */
      auto xn =  nearest(x*Twoopi<double>());
      auto y  =  fma(xn, mp2, fma(xn, mp1, x)); 
      auto n = quadrant(xn); 
      auto da = xn * mp3;
      auto a = y - da;
      da = (y - a) - da;
     
      return std::make_tuple(n, a, da); 
    }
  }
}

#endif
