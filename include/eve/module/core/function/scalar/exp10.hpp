//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXP10_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXP10_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/toint.hpp>
#include <eve/function/tofloat.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/maxlog10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/invlog10_2.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>  
#include <eve/platform.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto exp10_(EVE_SUPPORTS(cpu_)
                                     , T x) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using vt_t =  value_type_t<T>;
      using it_t =  as_integer_t<T>; 
      const T Log10_2hi =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      const T Log10_2lo =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
      if (is_greater_equal(x, Maxlog10<T>())) return Inf<T>();
      if (is_less_equal(x, Minlog10<T>())) return Zero<T>();
      auto c = nearest(Invlog10_2<T>()*x);
      auto k = it_t(c);
      x = fnma(c, Log10_2hi, x); //x-c*L
      x = fnma(c, Log10_2lo, x);   
      if constexpr(std::is_same_v<vt_t, float>)
      {
        // Remez polynom of degree 5 on [-0.5, 0.5]*log10(2) for (exp10(x)-1)/x   tested in range: [-37.9, 38.2308]
        //  2217772528 values computed.
        //  2198853506 values (99.15%)  within 0.0 ULPs
        //  18919022 values (0.85%)   within 0.5 ULPs
        //      5.2 cycles/value  (SSE4.2 g++-4.8)
        c = inc(horn<T,
                0x40135d8e, //    2.3025851e+00
                0x4029a926, //    2.6509490e+00
                0x400237da, //    2.0346589e+00
                0x3f95eb4c, //    1.1712432e+00
                0x3f0aacef, //    5.4170126e-01
                0x3e54dff1  //    2.0788552e-01
                >(x)*x);
      }
      else
      {
        T xx = sqr(x);
        T px = x*horn<T,
          0x40a2b4798e134a01ull,
          0x40796b7a050349e4ull,
          0x40277d9474c55934ull,
          0x3fa4fd75f3062dd4ull
          > (xx);
        T x2 =  px/(horn1<T,
                    0x40a03f37650df6e2ull,
                    0x4093e05eefd67782ull,
                    0x405545fdce51ca08ull
                    //   0x3ff0000000000000ull
                    > (xx)-px);
        c = inc(x2+x2);
      }
      return  ldexp(c, k);
    }
    else
    {
      return /*pedantic_*/(toint)(exp10(tofloat(x))); 
    }
  }

   template<typename T>
  EVE_FORCEINLINE constexpr auto exp10_(EVE_SUPPORTS(cpu_)
                                     , const pedantic_type &   
                                     , T x) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using vt_t =  value_type_t<T>;
      using it_t =  as_integer_t<T>; 
      const T Log10_2hi =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      const T Log10_2lo =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
      if (is_greater_equal(x, Maxlog10<T>())) return Inf<T>();
      if (is_less(x, Minlog10<T>())) return Zero<T>();
      auto c = nearest(Invlog10_2<T>()*x);
      auto k = it_t(c);
      x = fnma(c, Log10_2hi, x); //x-c*L
      x = fnma(c, Log10_2lo, x);   
      if constexpr(std::is_same_v<vt_t, float>)
      {
        // Remez polynom of degree 5 on [-0.5, 0.5]*log10(2) for (exp10(x)-1)/x   tested in range: [-37.9, 38.2308]
        //  2217772528 values computed.
        //  2198853506 values (99.15%)  within 0.0 ULPs
        //  18919022 values (0.85%)   within 0.5 ULPs
        //      5.2 cycles/value  (SSE4.2 g++-4.8)
        c = inc(horn<T,
                0x40135d8e, //    2.3025851e+00
                0x4029a926, //    2.6509490e+00
                0x400237da, //    2.0346589e+00
                0x3f95eb4c, //    1.1712432e+00
                0x3f0aacef, //    5.4170126e-01
                0x3e54dff1  //    2.0788552e-01
                >(x)*x);
      }
      else
      {
        T xx = sqr(x);
        T px = x*horn<T,
          0x40a2b4798e134a01ull,
          0x40796b7a050349e4ull,
          0x40277d9474c55934ull,
          0x3fa4fd75f3062dd4ull
          > (xx);
        T x2 =  px/(horn1<T,
                    0x40a03f37650df6e2ull,
                    0x4093e05eefd67782ull,
                    0x405545fdce51ca08ull
                    //   0x3ff0000000000000ull
                    > (xx)-px);
        c = inc(x2+x2);
      }
      return  pedantic_(ldexp)(c, k);
    }
    else
    {
      return /*pedantic_*/(toint)(exp10(tofloat(x))); 
    }
  } 
}

#endif
