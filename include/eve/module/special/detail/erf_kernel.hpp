//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

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
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  kernel1_erf1(const T& x, const T& ysq) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    T tmp = x
      *
      eve::reverse_horner(ysq, T(0x1.912c1535d121ap+11), T(0x1.797c38897528bp+8), T(0x1.c774e4d365da3p+6), T(0x1.949fb3ed443e9p+1), T(0x1.7c7905a31c322p-3))

      /
      eve::reverse_horner(ysq, T(0x1.63879423b87adp+11), T(0x1.40a77529cadc8p+10), T(0x1.e80c9d57e55b8p+7), T(0x1.799ee342fb2dep+4), T(0x1.0p0))
      ;
    return tmp;
  }

// computes erf(x) for double or double vectors
//  0.46875 <= abs(a0) <= 4.0
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  kernel1_erf2(const T&, const T& y) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    return
      eve::reverse_horner(y, T(0x1.3395b7fd2fc8ep+10), T(0x1.0062821236f6bp+11), T(0x1.ac030c15dc8d7p+10), T(0x1.b8f9e262b9fa3p+9), T(0x1.2aa2986aba462p+8), T(0x1.087a0d1c420d0p+6), T(0x1.1c42c35b8bc02p+3), T(0x1.20dd508eb103ep-1), T(0x1.71e703c5f5815p-26))

      /
      eve::reverse_horner(y, T(0x1.3395b7fd35f61p+10), T(0x1.adebc3fc90dbdp+11), T(0x1.10a9e7cb10e86p+12), T(0x1.9b599356d1202p+11), T(0x1.9558eeca29d27p+10), T(0x1.0c972e588749ep+9), T(0x1.d6c69b0ffcde7p+6), T(0x1.f7d66f486ded5p+3), T(0x1.0p0))
      ;
  }

// finalize for erf and erfc
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel1_finalize2(T& res, const T& y) noexcept
  {
    // Find a multiple of 1/16 that is within 1/16 of x.
    T ysq = trunc(16 * y) / 16;
    T del = (y - ysq) * (y + ysq);
    res   = exp(-ysq * ysq) * exp(-del) * res;
    return res;
  }

// computes erf(x) for double or double vectors
// 4 < abs(x)
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel1_erf3(const T&, const T& y) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    T Invsqrtpi = T(0.564189583547756286948079451561);
    T Xhuge     = T(6.71e+7);
    T ysq       = rec[pedantic2](sqr(y));
    T res       = ysq
      *
      eve::reverse_horner(ysq, T(0x1.595fd0d71e33cp-11), T(0x1.078448cd6c5b5p-6), T(0x1.0199d980a842fp-3), T(0x1.70fe40e2425b8p-2), T(0x1.38a78b9f065f6p-2), T(0x1.0b4fb18b485c7p-6))

      /
      eve::reverse_horner(ysq, T(0x1.32147a014bad1p-9), T(0x1.efc42917d7de7p-5), T(0x1.0e4993e122c39p-1), T(0x1.df79d6855f0adp+0), T(0x1.48c54508800dbp+1), T(0x1.0p0))
      ;
    res = if_else(is_greater(y, Xhuge), eve::zero, res);
    res = (Invsqrtpi - res) / y;
    return res;
  }

//  finalize for erfcx if x < 0
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel1_finalize3(T res, const T& x) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    // Find a multiple of 1/16 that is within 1/16 of x.
    T ysq = trunc(16 * x) / 16;
    T del = (x - ysq) * (x + ysq);
    T y   = exp(ysq * ysq) * exp(del);
    return if_else(
      x < -26.628, inf(as<T>()), (y + y) - res);
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
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel_erf1(const T& xx) noexcept requires(std::same_as<element_type_t<T>, float>)
  {
    return
      eve::reverse_horner(xx, T(0x1.20dd74p+0f), T(-0x1.8126fcp-2f), T(0x1.ce1e44p-4f), T(-0x1.b6c3e8p-6f), T(0x1.488d1ap-8f), T(-0x1.3f9076p-11f))
      ;
  }

// computes erfc(x)*exp(sqr(x)) for float or float vectors
// x >=  2/3
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel_erfc2(const T& z) noexcept requires(std::same_as<element_type_t<T>, float>)
  {
    // approximation of erfc(z1./(1-z1))).*exp((z1./(1-z1)).^2) (z1 =  z+0.4) on [0 0.5]
    // with a polynomial of degree 11 gives 16 ulp on [2/3 inf] for erfc
    // (exhaustive test against float(erfc(double(x))))
    // z is T z = x/inc(x)-T(0.4);
    T tmp =
      eve::reverse_horner(z, T(0x1.141d16p-1f), T(-0x1.2314c4p+0f), T(0x1.487050p-3f), T(0x1.8994dcp-2f), T(0x1.22eb8ep-3f), T(0x1.400de0p-3f), T(-0x1.5d50cap+0f), T(0x1.a160c6p+1f), T(-0x1.9a350ap+2f), T(0x1.acfc76p+2f), T(-0x1.506c22p+1f))
      ;
    return tmp;
  }

// computes erfc(x)*exp(sqr(x)) for float or float vectors
// x >=  2/3
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel_erfc3(const T& z) noexcept requires(std::same_as<element_type_t<T>, float>)
  {
    // approximation of erfc(z./(1-z))./(1-z) on [0 0.4]
    // with a polynomial of degree 8 gives 2 ulp on [0 2/3] for erfc
    // (exhaustive test against float(erfc(double(x))))
    // z is T z = x/inc(x);
    T tmp =
      eve::reverse_horner(z, T(0x1.fffffcp-1f), T(-0x1.06dafcp-3f), T(-0x1.422d30p+0f), T(-0x1.f92508p+0f), T(-0x1.2d930ap+1f), T(0x1.59fe76p-1f), T(-0x1.21b2acp+1f), T(0x1.36ad00p+1f), T(0x1.551caap+4f))
      ;
    return oneminus(z) * tmp;
  }

// computes erf(a0)/a0 for double or double vectors
// xx is sqr(a0) and 0 <= abs(a0) <= 0.65
  template<floating_ordered_value T>
  EVE_FORCEINLINE  constexpr T
  kernel_erf1(const T& xx) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    return
      eve::reverse_horner(xx, T(0x1.20dd750429b61p+0), T(0x1.16500f106c0a5p-3), T(0x1.4a59a4f02579cp-5), T(0x1.3b7664358865ap-10), T(0x1.10512d5b20332p-14))

      /
      eve::reverse_horner(xx, T(0x1.0000000000000p+0), T(0x1.d0a84eb1ca867p-2), T(0x1.64536ca92ea2fp-4), T(0x1.166f75999dbd1p-7), T(0x1.7ea4332348252p-12))
      ;
  }

// computes erfc(x)*exp(x*x) for double or double vectors
// 0.65 <= abs(x) <= 2.2
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  kernel_erfc2(const T& x) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    return
      eve::reverse_horner(x, T(0x1.ffffffbbb552bp-1), T(0x1.54dfe9b258a60p+0), T(0x1.c1986509e687bp-1), T(0x1.53dd7a67c7e9fp-2), T(0x1.2488a6b5cb5e5p-4), T(0x1.cf4cfe0aacbb4p-8), T(0x0.0p+0f))

      /

      eve::reverse_horner(x, T(0x1.0000000000000p+0), T(0x1.3adeae79b9708p+1), T(0x1.53b1052dca8bdp+1), T(0x1.9e677c2777c3cp+0), T(0x1.307622fcff772p-1), T(0x1.033c113a7deeep-3), T(0x1.9a996639b0d00p-7))
      ;
  }

// computes erfc(x)*exp(x*x) for double or double vectors
// 2.2 <= abs(x) <= 6
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  kernel_erfc3(const T& x) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    return
    eve::reverse_horner(x, T(0x1.fff5a9e697ae2p-1), T(0x1.9fa202deb88e5p+0), T(0x1.44744306832aep+0), T(0x1.29be1cff90d94p-1), T(0x1.42210f88b9d43p-3), T(0x1.71d0907ea7a92p-6), T(0x0.0p+0f))

      /
      eve::reverse_horner(x, T(0x1.0000000000000p+0), T(0x1.602f24bf3fdb6p+1), T(0x1.afd487397568fp+1), T(0x1.315ffdfd5ce91p+1), T(0x1.0cfd4cb6cde9fp+0), T(0x1.1d7ab774bb837p-2), T(0x1.47bd61bbb3843p-5))
      ;
  }

// computes erfc(rx)*exp(rx*rx) for double or double vectors
// x >=  6 rx = 1/x
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  erfc4(const T& rx) noexcept requires(std::same_as<element_type_t<T>, double>)
  {
    return
    eve::reverse_horner(rx, T(-0x1.e4ad1ec7d0000p-56), T(0x1.20dd750429a16p-1), T(0x1.60000e984b501p-36), T(-0x1.20dd753ae5dfdp-2), T(0x1.07e71e046a820p-22), T(0x1.b1494cac06d39p-2), T(0x1.4a451701654f1p-12), T(-0x1.105e6b8ef1a63p+0), T(0x1.505a857e9ccc8p-4), T(0x1.74fbabc514212p+1), T(0x1.5ac7631f7ac4fp+2), T(-0x1.57e03041e9d8bp+5), T(0x1.5803d26c4ec4fp+6), T(-0x1.05fce04ec4ec5p+6))
    ;
  }
}
