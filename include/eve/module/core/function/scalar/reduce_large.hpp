//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_LARGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_LARGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitwise_shr.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/two_split.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // x is always positive here TODO an ASSERT in def
  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , float const &x) noexcept
  {
    if (is_not_finite(x))
    {
      return std::tuple<float, float, float>{0.0f, Nan<float>(), 0.0f}; 
    }
    if (x <= 200.277f) //255*(pi/4)
    {
      return reduce_fast(x); 
    }
    else
    {
      // Table with 4/PI to 192 bit precision.  To avoid unaligned accesses
      //   only 8 new bits are added per entry, making the table 4 times larger.  
      constexpr const uint32_t __inv_pio4[24] =
        {
          0xa2,       0xa2f9,   0xa2f983,   0xa2f9836e,
          0xf9836e4e, 0x836e4e44, 0x6e4e4415, 0x4e441529,
          0x441529fc, 0x1529fc27, 0x29fc2757, 0xfc2757d1,
          0x2757d1f5, 0x57d1f534, 0xd1f534dd, 0xf534ddc0,
          0x34ddc0db, 0xddc0db62, 0xc0db6295, 0xdb629599,
          0x6295993c, 0x95993c43, 0x993c4390, 0x3c439041
        };
      constexpr const double pi63 = 0x1.921FB54442D18p-62;/* 2PI * 2^-64.  */
      auto xi =  bitwise_cast(x, as_<uint32_t>()); 
      const uint32_t *arr = &__inv_pio4[(xi >> 26) & 15];
      int shift = (xi >> 23) & 7;
      uint64_t n, res0, res1, res2;
      
      xi = (xi & 0xffffff) | 0x800000;
      xi <<= shift;
      
      res0 = xi * arr[0];
      res1 = (uint64_t)xi * arr[4];
      res2 = (uint64_t)xi * arr[8];
      res0 = (res2 >> 32) | (res0 << 32);
      res0 += res1;
      
      n = (res0 + (1ULL << 61)) >> 62;
      res0 -= n << 62;
      double xx = (int64_t)res0;
      return std::tuple<float, float, float>(static_cast<float>(n), static_cast<float>(xx * pi63), 0.0f);
    }
  }
   
  EVE_FORCEINLINE auto pass(double x1)
  {
    constexpr int HIGH_HALF = 1;     
    using mynumber = union { std::int32_t i[2]; double x; };
    double toverp[75] = { /*  2/ PI base 24*/
      10680707.0,  7228996.0,  1387004.0,  2578385.0, 16069853.0,
      12639074.0,  9804092.0,  4427841.0, 16666979.0, 11263675.0,
      12935607.0,  2387514.0,  4345298.0, 14681673.0,  3074569.0,
      13734428.0, 16653803.0,  1880361.0, 10960616.0,  8533493.0,
      3062596.0,  8710556.0,  7349940.0,  6258241.0,  3772886.0,
      3769171.0,  3798172.0,  8675211.0, 12450088.0,  3874808.0,
      9961438.0,   366607.0, 15675153.0,  9132554.0,  7151469.0,
      3571407.0,  2607881.0, 12013382.0,  4155038.0,  6285869.0,
      7677882.0, 13102053.0, 15825725.0,   473591.0,  9065106.0,
      15363067.0,  6271263.0,  9264392.0,  5636912.0,  4652155.0,
      7056368.0, 13614112.0, 10155062.0,  1944035.0,  9527646.0,
      15080200.0,  6658437.0,  6231200.0,  6832269.0, 16767104.0,
      5075751.0,  3212806.0,  1398474.0,  7579849.0,  6349435.0,
      12618859.0,  4703257.0, 12806093.0, 14477321.0,  2786137.0,
      12875403.0,  9837734.0, 14528324.0, 13719321.0,   343717.0 };
    double   t576 = Constant<double, 0x63f0000000000000ULL>();  /* 2 ^ 576  */              
    double   tm24 = Constant<double, 0x3e70000000000000ULL>();  /* 2 ^- 24  */              
    double    big = Constant<double, 0x4338000000000000ULL>();  /*  6755399441055744      */
    double   big1 = Constant<double, 0x4358000000000000ULL>();  /* 27021597764222976      */
    double sum = 0; 
    int k; 
    mynumber u; 
    u.x = x1;
    k = (u.i[HIGH_HALF]>>20)&2047;
    k = (k-450)/24;
    k = eve::max(k, 0);
    mynumber gor;
    gor.x = t576;
    gor.i[HIGH_HALF] -= ((k*24)<<20);
    double r[6]; 
    for (int i=0;i<6;++i)
    {
      r[i] = x1*toverp[k+i]*gor.x;
      gor.x *= tm24;
    }
    double s; 
    for (int i=0;i<3;++i) {
      s=(r[i]+big)-big;
      sum+=s;
      r[i]-=s;
    }
    double t=0;
    for (int i=0;i<6;++i)  t+=r[5-i];
    double bb=(((((r[0]-t)+r[1])+r[2])+r[3])+r[4])+r[5];
    s=(t+big)-big;
    sum+=s;
    t-=s;
    double b=t+bb;
    bb=(t-b)+bb;
    s=(sum+big1)-big1;
    sum-=s;
    return std::tuple<double, double, double>(sum, b, bb); 
  }; 
  
  EVE_FORCEINLINE auto pass1(double x1)
  {
    using ui64_t = uint64_t;
    using i32_t = struct{ int32_t lo; int32_t hi; }; //TODO endianess pb in view
    double toverp[75] = { /*  2/ PI base 24*/
      10680707.0,  7228996.0,  1387004.0,  2578385.0, 16069853.0,
      12639074.0,  9804092.0,  4427841.0, 16666979.0, 11263675.0,
      12935607.0,  2387514.0,  4345298.0, 14681673.0,  3074569.0,
      13734428.0, 16653803.0,  1880361.0, 10960616.0,  8533493.0,
      3062596.0,  8710556.0,  7349940.0,  6258241.0,  3772886.0,
      3769171.0,  3798172.0,  8675211.0, 12450088.0,  3874808.0,
      9961438.0,   366607.0, 15675153.0,  9132554.0,  7151469.0,
      3571407.0,  2607881.0, 12013382.0,  4155038.0,  6285869.0,
      7677882.0, 13102053.0, 15825725.0,   473591.0,  9065106.0,
      15363067.0,  6271263.0,  9264392.0,  5636912.0,  4652155.0,
      7056368.0, 13614112.0, 10155062.0,  1944035.0,  9527646.0,
      15080200.0,  6658437.0,  6231200.0,  6832269.0, 16767104.0,
      5075751.0,  3212806.0,  1398474.0,  7579849.0,  6349435.0,
      12618859.0,  4703257.0, 12806093.0, 14477321.0,  2786137.0,
      12875403.0,  9837734.0, 14528324.0, 13719321.0,   343717.0 };
    uint64_t  t576 = 0x63f0000000000000ULL;                      /* 2 ^ 576  */              
    double    tm24 = Constant<double, 0x3e70000000000000ULL>();  /* 2 ^- 24  */              
    double     big = Constant<double, 0x4338000000000000ULL>();  /*  6755399441055744      */
    double    big1 = Constant<double, 0x4358000000000000ULL>();  /* 27021597764222976      */
    double sum(0);
    ui64_t zero_lo(0xFFFFFFFF00000000ULL);
    ui64_t tmp0 = bitwise_cast(x1, as_<ui64_t>());
  
    alignas(sizeof(double)) i32_t k =  bitwise_cast(bitwise_and(tmp0, zero_lo), as_<i32_t>());
    k.hi =  bitwise_shr(k.hi, 20) & 2047;
    k.hi = eve::max((k.hi-450)/24, 0);
    
    alignas(sizeof(double)) auto tmp = bitwise_cast(t576, as_<i32_t>());
    tmp.hi -= shl(k.hi*24, 20); 
    
    double gor = bitwise_cast(tmp, double_);
    k.hi = eve::max(k.hi, 0);
    double r[6];
    auto inds = shr(bitwise_cast(k, as<ui64_t>()), 32); 
    for (int i=0;i<6;++i)
    {
      auto values = toverp[inds];
      inds = inc(inds); 
      r[i] = x1*values*gor;
      gor *= tm24;
    }
    double s; 
    for (int i=0;i<3;++i) {
      s=(r[i]+big)-big;
      sum+=s;
      r[i]-=s;
    }
    double t(0);
    for (int i=0;i<6;++i)  t+=r[5-i];
    double bb=(((((r[0]-t)+r[1])+r[2])+r[3])+r[4])+r[5];
    s=(t+big)-big;
    sum+=s;
    t-=s;
    double b=t+bb;
    bb=(t-b)+bb;
    s=(sum+big1)-big1;
    sum-=s;
    return std::tuple<double, double, double>(sum, b, bb); 
  }; 
  
  EVE_FORCEINLINE auto pass2(double x1)
  {
    using ui64_t = uint64_t;
    using i32_t = struct{ int32_t lo; int32_t hi; }; //TODO endianess pb in view
    double toverp[75] = { /*  2/ PI base 24*/
      10680707.0,  7228996.0,  1387004.0,  2578385.0, 16069853.0,
      12639074.0,  9804092.0,  4427841.0, 16666979.0, 11263675.0,
      12935607.0,  2387514.0,  4345298.0, 14681673.0,  3074569.0,
      13734428.0, 16653803.0,  1880361.0, 10960616.0,  8533493.0,
      3062596.0,  8710556.0,  7349940.0,  6258241.0,  3772886.0,
      3769171.0,  3798172.0,  8675211.0, 12450088.0,  3874808.0,
      9961438.0,   366607.0, 15675153.0,  9132554.0,  7151469.0,
      3571407.0,  2607881.0, 12013382.0,  4155038.0,  6285869.0,
      7677882.0, 13102053.0, 15825725.0,   473591.0,  9065106.0,
      15363067.0,  6271263.0,  9264392.0,  5636912.0,  4652155.0,
      7056368.0, 13614112.0, 10155062.0,  1944035.0,  9527646.0,
      15080200.0,  6658437.0,  6231200.0,  6832269.0, 16767104.0,
      5075751.0,  3212806.0,  1398474.0,  7579849.0,  6349435.0,
      12618859.0,  4703257.0, 12806093.0, 14477321.0,  2786137.0,
      12875403.0,  9837734.0, 14528324.0, 13719321.0,   343717.0 };
    uint64_t  t576 = 0x63f0000000000000ULL;                      /* 2 ^ 576  */              
    double    tm24 = Constant<double, 0x3e70000000000000ULL>();  /* 2 ^- 24  */              
    double     big = Constant<double, 0x4338000000000000ULL>();  /*  6755399441055744      */
    double    big1 = Constant<double, 0x4358000000000000ULL>();  /* 27021597764222976      */
    double sum(0);
    ui64_t zero_lo(0xFFFFFFFF00000000ULL);
    auto z = bitwise_and(zero_lo, x1); 
    i32_t k;
    k.hi = int32_t(z >> 32);
    k.lo = int32_t(z & 0x00000000FFFFFFFFULL);
    k.hi =  bitwise_shr(k.hi, 20) & 2047;
    k.hi = eve::max((k.hi-450)/24, 0);
    
    i32_t tmp;
    tmp.hi = int32_t(t576 >> 32);
    tmp.lo = int32_t(t576 & 0x00000000FFFFFFFFULL);
    tmp.hi -= shl(k.hi*24, 20); 
    
    double gor = bitwise_cast(tmp, double_);
    double r[6];
    auto inds = shr(bitwise_cast(k, as<ui64_t>()), 32); 
    for (int i=0;i<6;++i)
    {
      auto values = toverp[inds];
      inds = inc(inds); 
      r[i] = x1*values*gor;
      gor *= tm24;
    }
    double s; 
    for (int i=0;i<3;++i) {
      s=(r[i]+big)-big;
      sum+=s;
      r[i]-=s;
    }
    double t(0);
    for (int i=0;i<6;++i)  t+=r[5-i];
    double bb=(((((r[0]-t)+r[1])+r[2])+r[3])+r[4])+r[5];
    s=(t+big)-big;
    sum+=s;
    t-=s;
    double b=t+bb;
    bb=(t-b)+bb;
    s=(sum+big1)-big1;
    sum-=s;
    return std::tuple<double, double, double>(sum, b, bb); 
  }; 

  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , double const &xx) noexcept
  {
    //  return rem_pio2(xx);
    if (eve::abs(xx) <= Pio_4<double>()) return std::tuple(0.0, xx, 0.0); 
    // for x less than 9.23297861778572e-128 (smallestposval*2^600)
    //   and greater than 2.20131364292740010161e-134  the following routine is incorrect
    //   because  of the denormality of x*2^600 
    //   it should return x inchanged in *a and *da 0 */

    if (is_not_finite(xx)) return std::tuple<double, double, double>{0.0, Nan<double>(), 0.0}; 
    double  tm600 = Constant<double, 0x1a70000000000000ULL>();  /* 2 ^- 600 */              
    double  split = Constant<double, 0x41a0000002000000ULL>();  /* 2^27 + 1 */   
    double    hp0 = Constant<double, 0x3FF921FB54442D18ULL>();  /* 1.5707963267948966     */
    double    hp1 = Constant<double, 0x3C91A62633145C07ULL>();  /* 6.123233995736766e-17  */
    double    mp1 = Constant<double, 0x3FF921FB58000000ULL>();  /* 1.5707963407039642     */
    double    mp2 = Constant<double, 0xBE4DDE9740000000ULL>();  /*-1.3909067675399456e-08 */
    double x = xx*tm600;
    auto [x1, x2] =  two_split(x);
    auto [sum1, b1, bb1] = pass2(x1);
    auto [sum2, b2, bb2] = pass2(x2);
    double sum =  sum1+sum2; 
    double b=b1+b2;
    double bb = (eve::abs(b1)>eve::abs(b2))? (b1-b)+b2 : (b2-b)+b1;
    if (b > 0.5)
    {
      b-=1.0;
      sum+=1.0;
    }
    else if (b < -0.5)
    {
      b+=1.0;
      sum-=1.0;
    }
    double s=b+(bb+bb1+bb2);
    double t=((b-s)+bb)+(bb1+bb2);
    b=s*split;
    double t1=b-(b-s);
    double t2=s-t1;
    b=s*hp0;
    {
      auto z1 = t1*mp1;
      auto z2 = t1*mp2;
      auto z3 = t2*mp1;
      auto z4 = t2*mp2; 
      auto z5 = s*hp1;
      auto z6 = t*hp0;
      bb = (((z1-b)+z2)+z3)+(z4+z5+z6); 
    }
    
    s=b+bb;
    t=(b-s)+bb;
    return std::tuple<double, double, double>(static_cast<double>((int) sum&3), s, t);
   }
}

#endif
