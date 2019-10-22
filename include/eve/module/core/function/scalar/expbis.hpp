//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXPBIS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXPBIS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
//#include <eve/function/toint.hpp> TODO
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
//#include <eve/module/core/detail/generic/expbis_kernel.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>


// #define N (1 << EXP2F_TABLE_BITS)

// const struct exp2f_data __exp2f_data = {
//   /* tab[i] = uint(2^(i/N)) - (i << 52-BITS)
//      used for computing 2^(k/N) for an int |k| < 150 N as
//      double(tab[k%N] + (k << 52-BITS)) */
//   .tab = {
// 0x3ff0000000000000, 0x3fefd9b0d3158574, 0x3fefb5586cf9890f, 0x3fef9301d0125b51,
// 0x3fef72b83c7d517b, 0x3fef54873168b9aa, 0x3fef387a6e756238, 0x3fef1e9df51fdee1,
// 0x3fef06fe0a31b715, 0x3feef1a7373aa9cb, 0x3feedea64c123422, 0x3feece086061892d,
// 0x3feebfdad5362a27, 0x3feeb42b569d4f82, 0x3feeab07dd485429, 0x3feea47eb03a5585,
// 0x3feea09e667f3bcd, 0x3fee9f75e8ec5f74, 0x3feea11473eb0187, 0x3feea589994cce13,
// 0x3feeace5422aa0db, 0x3feeb737b0cdc5e5, 0x3feec49182a3f090, 0x3feed503b23e255d,
// 0x3feee89f995ad3ad, 0x3feeff76f2fb5e47, 0x3fef199bdd85529c, 0x3fef3720dcef9069,
// 0x3fef5818dcfba487, 0x3fef7c97337b9b5f, 0x3fefa4afa2a490da, 0x3fefd0765b6e4540,
//   },
//   .shift_scaled = 0x1.8p+52 / N,
//   .poly = { 0x1.c6af84b912394p-5, 0x1.ebfce50fac4f3p-3, 0x1.62e42ff0c52d6p-1 },
//   .shift = 0x1.8p+52,
//   .invln2_scaled = 0x1.71547652b82fep+0 * N,
//   .poly_scaled = {
// 0x1.c6af84b912394p-5/N/N/N, 0x1.ebfce50fac4f3p-3/N/N, 0x1.62e42ff0c52d6p-1/N
//   },
// };
// EXP2F_TABLE_BITS = 5
// EXP2F_POLY_ORDER = 3

// #define N (1 << EXP2F_TABLE_BITS)
// #define InvLn2N __exp2f_data.invln2_scaled
// #define T __exp2f_data.tab
// #define C __exp2f_data.poly_scaled


namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE auto expbis_(EVE_SUPPORTS(cpu_)
                                     , T x) noexcept
  requires(T, floating_point<T>)
  {
    if (is_greater_equal(x, Maxlog<T>())) return Inf<T>();
    if (is_less_equal(x, Minlog<T>())) return Zero<T>();
    if constexpr(eve::platform::supports_nans) if (is_nan(x)) return x;
    constexpr int EXP2F_TABLE_BITS = 5; 
    constexpr int EXP2F_POLY_ORDER = 3; 
    constexpr int N = (1 << EXP2F_TABLE_BITS); 
    constexpr double invln2_scaled = 0x1.71547652b82fep+0 * N; 
    // tab[i] = uint(2^(i/N)) - (i << 52-BITS)
    // used for computing 2^(k/N) for an int |k| < 150 N as
    // double(tab[k%N] + (k << 52-BITS)) 
    static uint64_t tab[N] = {
      0x3ff0000000000000ULL, 0x3fefd9b0d3158574ULL, 0x3fefb5586cf9890fULL, 0x3fef9301d0125b51ULL,
      0x3fef72b83c7d517bULL, 0x3fef54873168b9aaULL, 0x3fef387a6e756238ULL, 0x3fef1e9df51fdee1ULL,
      0x3fef06fe0a31b715ULL, 0x3feef1a7373aa9cbULL, 0x3feedea64c123422ULL, 0x3feece086061892dULL,
      0x3feebfdad5362a27ULL, 0x3feeb42b569d4f82ULL, 0x3feeab07dd485429ULL, 0x3feea47eb03a5585ULL,
      0x3feea09e667f3bcdULL, 0x3fee9f75e8ec5f74ULL, 0x3feea11473eb0187ULL, 0x3feea589994cce13ULL,
      0x3feeace5422aa0dbULL, 0x3feeb737b0cdc5e5ULL, 0x3feec49182a3f090ULL, 0x3feed503b23e255dULL,
      0x3feee89f995ad3adULL, 0x3feeff76f2fb5e47ULL, 0x3fef199bdd85529cULL, 0x3fef3720dcef9069ULL,
      0x3fef5818dcfba487ULL, 0x3fef7c97337b9b5fULL, 0x3fefa4afa2a490daULL, 0x3fefd0765b6e4540ULL,
    }; 
    static double poly_scaled[EXP2F_POLY_ORDER] = {
      0x1.c6af84b912394p-5/N/N/N,
      0x1.ebfce50fac4f3p-3/N/N,
      0x1.62e42ff0c52d6p-1/N
    }; 
    // x*N/Ln2 = k + r with r in [-1/2, 1/2] and int k. 
    auto z = invln2_scaled * double(x);
    auto kd = nearest(z);
    uint64_t ki = lround(z);  
    auto r = z - kd;
    
    /* exp(x) = 2^(k/N) * 2^(r/N) ~= s * (poly_scaled0*r^3 + poly_scaled1*r^2 + poly_scaled2*r + 1) */
    auto t = tab[ki % N];
    t += ki << (52 - EXP2F_TABLE_BITS);
    auto s = bitwise_cast(t, double_ );
    z = fma(poly_scaled[0], r,  poly_scaled[1]);
    auto r2 = sqr(r);
    auto y = fma(poly_scaled[2], r, One<double>());
    y = fma(z, r2, y);
    y = y * s;
    return (float) y;
  }
  
}

#endif

 //      using vt_t =  value_type_t<T>;
//     using it_t =  as_integer_t<T>; 
//     const T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
//     const T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
//     const T Invlog_2=  Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
//     if (is_greater_equal(x, Maxlog<T>())) return Inf<T>();
//     if (is_less_equal(x, Minlog<T>())) return Zero<T>();
//     if constexpr(eve::platform::supports_nans) if (is_nan(x)) return x;
//     // reduce
//     auto c = nearest(Invlog_2*x);
//     auto k = it_t(c);
//     x = fnma(c, Log_2hi, x); //x-c*L
//     if constexpr(std::is_same_v<vt_t, float>)
//     {
//       x = fnma(c, Log_2lo, x);   
//       // Remez polynomial of degree 4 on [-0.5 0.5] for (expbis(x)-1-x)/sqr(x)
//       // tested in range: [-88.3763, 88.3763]
//       //2214928753 values (98.98%)  within 0.0 ULPs
//       //  22831063 values (1.02%)   within 0.5 ULPs
//       //  4.89648 cycles/value (SSE4.2 g++-4.8)
//       T y = horn<T,
//         0x3f000000, //  5.0000000e-01
//         0x3e2aa9a5, //  1.6666277e-01
//         0x3d2aa957, //  4.1665401e-02
//         0x3c098d8b, //  8.3955629e-03
//         0x3ab778cf  //  1.3997796e-03
//         >(x);
//       c = inc(fma(y, sqr(x), x));
//     }
//     else
//     {
//       T hi = x;
//       T lo = c*Log_2lo;
//       x = hi-lo; 
//       T t = sqr(x);
//       c = fnma(t, horn<T
//               , 0x3fc555555555553eull
//               , 0xbf66c16c16bebd93ull
//               , 0x3f11566aaf25de2cull
//               , 0xbebbbd41c5d26bf1ull
//               , 0x3e66376972bea4d0ull
//                >(t), x); //x-h*t
//       c = oneminus((((lo-(x*c)/(T(2)-c))-hi)));
//     }
//     return  ldexp(c, k);
//   }
