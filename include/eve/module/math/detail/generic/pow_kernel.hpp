//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

namespace eve::detail
{
  template<floating_value T>
  EVE_FORCEINLINE T
  kernel_pow1(const T& x, const T& z) noexcept
  {
    if constexpr( std::is_same_v<element_type_t<T>, float> )
    {
      return z * x *  eve::reverse_horner(x, T(0x1.555546p-2f), T(-0x1.00002ap-2f)
                                         , T(0x1.9a5f46p-3f), T(-0x1.54c364p-3f)) ;
    }
    else if constexpr( std::is_same_v<element_type_t<T>, double> )
    {
      return x * (z * eve::reverse_horner(x, T(0x1.2aa83b65c9b74p+2), T(0x1.eccbd7f78eb6fp+2)
                                         , T(0x1.dddefea9edf15p+1), T(0x1.fdb997f5b5cf0p-2))
                  /
                  eve::reverse_horner(x, T(0x1.bffc5918ae92ep+3), T(0x1.0ccbc1b176402p+5)
                                     , T(0x1.bffff41c1c9f5p+4), T(0x1.2aab49b20914ep+3), T(0x1.0p0))
                 );
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE T
  kernel_pow2(const T& x) noexcept
  {
    if constexpr( std::is_same_v<element_type_t<T>, float> )
    {
      return
        eve::reverse_horner(x, T(0x1.62e430p-1f), T(0x1.ebfbc2p-3f), T(0x1.c69a70p-5f), T(0x1.349378p-7f))
        ;
    }
    else if constexpr( std::is_same_v<element_type_t<T>, double> )
    {
      return
        eve::reverse_horner(x, T(0x1.62e42fefa39efp-1), T(0x1.ebfbdff82c56dp-3), T(0x1.c6b08d7041a92p-5)
                           , T(0x1.3b2ab6ef133b7p-7), T(0x1.5d87ec84aef1dp-10)
                           , T(0x1.42fbe60fc9259p-13), T(0x1.f6307d7f2937fp-17));
    }
  }

  template<integral_value I>
  EVE_FORCEINLINE as_floating_point_t<I>
  twomio16(const I                &i) noexcept
  {
    /* 2^(-i/16)
     * The decimal values are rounded to 24-bit precision
     */
    using elt_t = as_floating_point_t<element_type_t<I>>;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      const elt_t A[17] = {elt_t(1.00000000000000000000E0),
                           elt_t(9.57603275775909423828125E-1),
                           elt_t(9.17004048824310302734375E-1),
                           elt_t(8.78126084804534912109375E-1),
                           elt_t(8.40896427631378173828125E-1),
                           elt_t(8.05245161056518554687500E-1),
                           elt_t(7.71105408668518066406250E-1),
                           elt_t(7.38413095474243164062500E-1),
                           elt_t(7.07106769084930419921875E-1),
                           elt_t(6.77127778530120849609375E-1),
                           elt_t(6.48419797420501708984375E-1),
                           elt_t(6.20928883552551269531250E-1),
                           elt_t(5.94603538513183593750000E-1),
                           elt_t(5.69394290447235107421875E-1),
                           elt_t(5.45253872871398925781250E-1),
                           elt_t(5.22136867046356201171875E-1),
                           elt_t(5.00000000000000000000E-1)};
      if constexpr( scalar_value<I> ) return A[i];
      else return gather(&A[0], i);
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      const elt_t A[17] = {elt_t(1.00000000000000000000E0),
                           elt_t(9.57603280698573700036E-1),
                           elt_t(9.17004043204671215328E-1),
                           elt_t(8.78126080186649726755E-1),
                           elt_t(8.40896415253714502036E-1),
                           elt_t(8.05245165974627141736E-1),
                           elt_t(7.71105412703970372057E-1),
                           elt_t(7.38413072969749673113E-1),
                           elt_t(7.07106781186547572737E-1),
                           elt_t(6.77127773468446325644E-1),
                           elt_t(6.48419777325504820276E-1),
                           elt_t(6.20928906036742001007E-1),
                           elt_t(5.94603557501360513449E-1),
                           elt_t(5.69394317378345782288E-1),
                           elt_t(5.45253866332628844837E-1),
                           elt_t(5.22136891213706877402E-1),
                           elt_t(5.00000000000000000000E-1)};
      if constexpr( scalar_value<I> ) return A[i];
      else return gather(&A[0], i);
    }
  }

  template<integral_value I>
  EVE_FORCEINLINE auto
  continuation(const I& i) noexcept
  {
    /* continuation, for even i only
     * 2^(i/16)  =  A[i] + B[i/2]
     */
    using elt_t = as_floating_point_t<element_type_t<I>>;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      const elt_t B[9] = {elt_t(0.00000000000000000000E0),
                          elt_t(-5.61963907099083340520586E-9),
                          elt_t(-1.23776636307969995237668E-8),
                          elt_t(4.03545234539989593104537E-9),
                          elt_t(1.21016171044789693621048E-8),
                          elt_t(-2.00949968760174979411038E-8),
                          elt_t(1.89881769396087499852802E-8),
                          elt_t(-6.53877009617774467211965E-9),
                          elt_t(0.00000000000000000000E0)};
      if constexpr( scalar_value<I> ) return B[i];
      else return gather(&B[0], i);
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      const elt_t B[9] = {elt_t(0.00000000000000000000E0),
                          elt_t(1.64155361212281360176E-17),
                          elt_t(4.09950501029074826006E-17),
                          elt_t(3.97491740484881042808E-17),
                          elt_t(-4.83364665672645672553E-17),
                          elt_t(1.26912513974441574796E-17),
                          elt_t(1.99100761573282305549E-17),
                          elt_t(-1.52339103990623557348E-17),
                          elt_t(0.00000000000000000000E0)};
      if constexpr( scalar_value<I> ) return B[i];
      else return gather(&B[0], i);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE auto
  kernel_select(const T& xx) noexcept
  {
    using i_t = as_integer_t<T>;
    // find significand in antilog table A[]
    i_t i    = one(eve::as<i_t>());
    i        = if_else(is_less_equal(xx, twomio16(i_t(9))), i_t(9), i);
    i        = add[is_less_equal(xx, twomio16(i + 4))](i, i_t(4));
    i        = add[is_less_equal(xx, twomio16(i + 2))](i, i_t(2));
    i        = if_else(is_greater_equal(xx, twomio16(one(eve::as<i_t>()))), i_t(-1), i);
    i        = inc(i);
    T    tmp = twomio16(i);
    auto x   = xx - tmp;
    x -= continuation(i >> 1);
    x /= tmp;
    return kumi::make_tuple(x, i);
  }

}
