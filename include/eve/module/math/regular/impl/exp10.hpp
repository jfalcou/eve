//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/core/regular/sqr.hpp> // THIS IS A PROBLEM SUPPRESS
#include <eve/module/math/constant/invlog10_2.hpp>
#include <eve/module/math/constant/maxlog10.hpp>
#include <eve/module/math/constant/minlog10.hpp>
#include <eve/module/math/constant/minlog10denormal.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr T
exp10_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
    requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t    = element_type_t<T>;
    auto minlogval = []()
    {
      if constexpr( (!eve::platform::supports_denormals) || std::is_same_v<D, regular_type> )
      {
        return minlog10(eve::as<T>());
      }
      else { return minlog10denormal(eve::as<T>()); }
    };
    const T Log10_2hi   = Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
    const T Log10_2lo   = Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
    auto    xltminlog10 = x <= minlogval();
    auto    xgemaxlog10 = x >= maxlog10(eve::as(x));
    if constexpr( scalar_value<T> )
    {
      if( xgemaxlog10 ) return inf(eve::as(x));
      if( xltminlog10 ) return zero(eve::as(x));
    }
    auto c = nearest(invlog10_2(eve::as<T>()) * x);
    auto k = c;
    x      = fnma(c, Log10_2hi, x); // x-c*L
    x      = fnma(c, Log10_2lo, x);
    if constexpr( std::is_same_v<elt_t, float> )
    {
      c = inc(horn<T, 0x40135d8e, 0x4029a926, 0x400237da, 0x3f95eb4c, 0x3f0aacef, 0x3e54dff1>(x)
              * x);
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      T xx = sqr(x);
      T px = x
             * horn<T,
                    0x40a2b4798e134a01ull,
                    0x40796b7a050349e4ull,
                    0x40277d9474c55934ull,
                    0x3fa4fd75f3062dd4ull>(xx);
      T x2 = px
             / (horn1<T, 0x40a03f37650df6e2ull, 0x4093e05eefd67782ull, 0x405545fdce51ca08ull>(xx)
                - px);
      c = inc(x2 + x2);
    }
    auto z = pedantic(ldexp)(c, k);
    if constexpr( simd_value<T> )
    {
      z = if_else(xltminlog10, eve::zero, z);
      z = if_else(xgemaxlog10, inf(eve::as(x)), z);
    }
    return z;
  }
  else return apply_over(D()(exp10), x);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr T
exp10_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  return exp10(regular_type(), x);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
exp10_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::exp10, t);
}
}
