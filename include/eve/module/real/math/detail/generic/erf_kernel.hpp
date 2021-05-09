//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/constant.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>
#include <eve/module/real/core/detail/generic/horn1.hpp>
#include <concepts>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////
  // kernel1
  // defines kernel1_erf1
  // defines kernel1_erf2
  // defines kernel1_erf3
  // defines kernel1_finalize2
  // defines kernel1_finalize3

  // computes erf(a0) for double or double vectors
  // x is a0, y is abs(a0) and 0 <= abs(a0) <= 0.46875
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel1_erf1(const T& x,  const T & ysq) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    T tmp = x *  horn<T,
      0x40a912c1535d121all,
      0x407797c38897528bll,
      0x405c774e4d365da3ll,
      0x400949fb3ed443e9ll,
      0x3fc7c7905a31c322ll
      > (ysq)/
      horn1<T,
      0x40a63879423b87adll,
      0x40940a77529cadc8ll,
      0x406e80c9d57e55b8ll,
      0x403799ee342fb2dell
      //  0x3ff0000000000000ll
      > (ysq);
    return tmp;
  }

  // computes erf(x) for double or double vectors
  //  0.46875 <= abs(a0) <= 4.0
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel1_erf2(const T&, const T& y) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    return horn<T,
      0X4093395B7FD2FC8EULL,
      0X40A0062821236F6BULL,
      0X409AC030C15DC8D7ULL,
      0X408B8F9E262B9FA3ULL,
      0X4072AA2986ABA462ULL,
      0X405087A0D1C420D0ULL,
      0X4021C42C35B8BC02ULL,
      0X3FE20DD508EB103EULL,
      0X3E571E703C5F5815ULL
      > (y)/
      horn1<T,
      0X4093395B7FD35F61ULL,
      0X40AADEBC3FC90DBDULL,
      0X40B10A9E7CB10E86ULL,
      0X40A9B599356D1202ULL,
      0X4099558EECA29D27ULL,
      0X4080C972E588749EULL,
      0X405D6C69B0FFCDE7ULL,
      0X402F7D66F486DED5ULL
      //   0X3FF0000000000000ULL
      > (y);
  }

  // finalize for erf and erfc
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel1_finalize2(T& res, const T& y) noexcept
  {
    // Find a multiple of 1/16 that is within 1/16 of x.
    T ysq = trunc(16*y)/16;
    T del = (y-ysq)*(y+ysq);
    res = exp(-ysq*ysq) * exp(-del) * res;
    return res;
  }


  // computes erf(x) for double or double vectors
  // 4 < abs(x)
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel1_erf3(const T& , const T& y) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    T Invsqrtpi = Constant<T, 0x3fe20dd750429b6dll>(); //0.564189583547756286948079451561
    T Xhuge     = Constant<T, 0x418ffeeb00000000ll>(); // 6.71e+7
    T ysq = rec(sqr(y));
    T res = ysq*
      horn<T,
      0X3F4595FD0D71E33CULL,
      0X3F9078448CD6C5B5ULL,
      0X3FC0199D980A842FULL,
      0X3FD70FE40E2425B8ULL,
      0X3FD38A78B9F065F6ULL,
      0X3F90B4FB18B485C7ULL
      > (ysq)/
      horn1<T,
      0X3F632147A014BAD1ULL,
      0X3FAEFC42917D7DE7ULL,
      0X3FE0E4993E122C39ULL,
      0X3FFDF79D6855F0ADULL,
      0X40048C54508800DBULL
      //  0X3FF0000000000000ULL
      > (ysq);
    res = if_else(is_greater(y, Xhuge), eve::zero, res);
    res = (Invsqrtpi -  res) / y;
    return res;
  }

  //  finalize for erfcx if x < 0
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel1_finalize3(T res, const T& x) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    // Find a multiple of 1/16 that is within 1/16 of x.
    T ysq = trunc(16*x)/16;
    T del = (x-ysq)*(x+ysq);
    T y = exp(ysq*ysq) * exp(del);
    return if_else(x < -26.628/*Constant<T, 0XC03AA0C49BA5E354ULL>()*/, inf(as<T>()), (y+y)-res); //-26.628
  }


  //////////////////////////////////////////////////////////////////
  // kernel
  // defines kernel_erf1
  // defines kernel_erfc2
  // defines kernel_erfc3
  // defines kernel_finalize2
  // defines kernel_finalize3



  // computes erf(a0)/a0 for float or float vectors
  // xx is sqr(a0) and 0 <= abs(x) <= 2/3
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erf1(const T& xx) noexcept
  requires(std::same_as<element_type_t<T>, float>)
  {
    return horn<T,
      0x3f906eba, //   1.128379154774254e+00
      0xbec0937e, //  -3.761252839094832e-01
      0x3de70f22, //   1.128218315189123e-01
      0xbcdb61f4, //  -2.678010670585737e-02
      0x3ba4468d, //   5.013293006147870e-03
      0xba1fc83b  //  -6.095205117313012e-04
      > (xx);
  }

  // computes erfc(x)*exp(sqr(x)) for float or float vectors
  // x >=  2/3
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erfc2(const T& z) noexcept
  requires(std::same_as<element_type_t<T>, float>)
  {
    // approximation of erfc(z1./(1-z1))).*exp((z1./(1-z1)).^2) (z1 =  z+0.4) on [0 0.5]
    // with a polynomial of degree 11 gives 16 ulp on [2/3 inf] for erfc
    // (exhaustive test against float(erfc(double(x))))
    // z is T z = x/inc(x)-T(0.4);
    T tmp =  horn<T,
      0x3f0a0e8b, //   5.392844046572836e-01
      0xbf918a62, //  -1.137035586823118e+00
      0x3e243828, //   1.603704761054187e-01
      0x3ec4ca6e, //   3.843569094305250e-01
      0x3e1175c7, //   1.420508523645926e-01
      0x3e2006f0, //   1.562764709849380e-01
      0xbfaea865, //  -1.364514006347145e+00
      0x4050b063, //   3.260765682222576e+00
      0xc0cd1a85, //  -6.409487379234005e+00
      0x40d67e3b, //   6.702908785399893e+00
      0xc0283611  //  -2.628299919293280e+00
      > (z);
    return tmp;
  }

  // computes erfc(x)*exp(sqr(x)) for float or float vectors
  // x >=  2/3
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erfc3(const T& z) noexcept
  requires(std::same_as<element_type_t<T>, float>)
  {
    // approximation of erfc(z./(1-z))./(1-z) on [0 0.4]
    // with a polynomial of degree 8 gives 2 ulp on [0 2/3] for erfc
    // (exhaustive test against float(erfc(double(x))))
    // z is T z = x/inc(x);
    T tmp = horn<T,
      0x3f7ffffe, //   9.9999988e-01
      0xbe036d7e, //  -1.2834737e-01
      0xbfa11698, //  -1.2585020e+00
      0xbffc9284, //  -1.9732213e+00
      0xc016c985, //  -2.3560498e+00
      0x3f2cff3b, //   6.7576951e-01
      0xc010d956, //  -2.2632651e+00
      0x401b5680, //   2.4271545e+00
      0x41aa8e55  //   2.1319498e+01
      > (z);
    return  oneminus(z)*tmp;
  }

  // computes erf(a0)/a0 for double or double vectors
  // xx is sqr(a0) and 0 <= abs(a0) <= 0.65
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erf1(const T& xx)  noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    return horn<T,
      0x3ff20dd750429b61ull, // 1.12837916709551
      0x3fc16500f106c0a5ull, // 0.135894887627278
      0x3fa4a59a4f02579cull, // 4.03259488531795E-02
      0x3f53b7664358865aull, // 1.20339380863079E-03
      0x3f110512d5b20332ull  // 6.49254556481904E-05
      > (xx)/
      horn<T,
      0x3ff0000000000000ull, // 1
      0x3fdd0a84eb1ca867ull, // 0.453767041780003
      0x3fb64536ca92ea2full, // 8.69936222615386E-02
      0x3f8166f75999dbd1ull, // 8.49717371168693E-03
      0x3f37ea4332348252ull  // 3.64915280629351E-04
      > (xx);
  }

  // computes erfc(x)*exp(x*x) for double or double vectors
  // 0.65 <= abs(x) <= 2.2
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erfc2(const T& x) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    return  horn<T,
      0x3feffffffbbb552bull, // 0.999999992049799
      0x3ff54dfe9b258a60ull, // 1.33154163936765
      0x3fec1986509e687bull, // 0.878115804155882
      0x3fd53dd7a67c7e9full, // 0.331899559578213
      0x3fb2488a6b5cb5e5ull, // 7.14193832506776E-02
      0x3f7cf4cfe0aacbb4ull, // 7.06940843763253E-03
      0x0ull                 // 0
      > (x)/
      horn<T,
      0x3ff0000000000000ull, // 1
      0x4003adeae79b9708ull, // 2.45992070144246
      0x40053b1052dca8bdull, // 2.65383972869776
      0x3ff9e677c2777c3cull, // 1.61876655543871
      0x3fe307622fcff772ull, // 0.594651311286482
      0x3fc033c113a7deeeull, // 0.126579413030178
      0x3f89a996639b0d00ull  // 1.25304936549413E-02
      > (x);
  }

  // computes erfc(x)*exp(x*x) for double or double vectors
  // 2.2 <= abs(x) <= 6
  template <floating_real_value T>
  EVE_FORCEINLINE T kernel_erfc3(const T& x) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    return   horn<T,
      0x3fefff5a9e697ae2ull, //0.99992114009714
      0x3ff9fa202deb88e5ull, //1.62356584489367
      0x3ff44744306832aeull, //1.26739901455873
      0x3fe29be1cff90d94ull, //0.581528574177741
      0x3fc42210f88b9d43ull, //0.157289620742839
      0x3f971d0907ea7a92ull, //2.25716982919218E-02
      0x0ll                  //0
      > (x)/
      horn<T,
      0x3ff0000000000000ull, //1
      0x400602f24bf3fdb6ull, //2.75143870676376
      0x400afd487397568full, //3.37367334657285
      0x400315ffdfd5ce91ull, //2.38574194785344
      0x3ff0cfd4cb6cde9full, //1.05074004614827
      0x3fd1d7ab774bb837ull, //0.278788439273629
      0x3fa47bd61bbb3843ull  //4.00072964526861E-02
      > (x);
  }

  // computes erfc(rx)*exp(rx*rx) for double or double vectors
  // x >=  6 rx = 1/x
  template <floating_real_value T>
  EVE_FORCEINLINE T erfc4(const T& rx) noexcept
  requires(std::same_as<element_type_t<T>, double>)
  {
    return  horn<T,
      0xbc7e4ad1ec7d0000ll,// -2.627435221016534e-17
      0x3fe20dd750429a16ll,// 5.641895835477182e-01
      0x3db60000e984b501ll,// 2.000889609806154e-11
      0xbfd20dd753ae5dfdll,// -2.820947949598745e-01
      0x3e907e71e046a820ll,// 2.457786367990903e-07
      0x3fdb1494cac06d39ll,// 4.231311779019112e-01
      0x3f34a451701654f1ll,// 3.149699042180451e-04
      0xbff105e6b8ef1a63ll,// -1.063940737150596e+00
      0x3fb505a857e9ccc8ll,// 8.211757799454056e-02
      0x40074fbabc514212ll,// 2.913930388669777e+00
      0x4015ac7631f7ac4fll,// 5.418419628850713e+00
      0xc0457e03041e9d8bll,// -4.298446704382794e+01
      0x4055803d26c4ec4fll,// 8.600373238783617e+01
      0xc0505fce04ec4ec5ll // -6.549694941594051e+01
      > (rx);
  }
}
