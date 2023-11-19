//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

template<unsigned_value N, floating_value T, floating_value U>
EVE_FORCEINLINE auto
fibonacci_(EVE_SUPPORTS(cpu_), N n, T a, U b) noexcept
{
  return indexed_call(fibonacci, n, a, b);
}

template<unsigned_value N, floating_value T>
EVE_FORCEINLINE auto
fibonacci_(EVE_SUPPORTS(cpu_), N n, T a, T b) noexcept
{
  if constexpr( has_native_abi_v<T> &&  has_native_abi_v<N>)
  {
    using w_t                 = as_wide_as_t<T, N>;
    using elt_t               = element_type_t<T>;
    using eli_t               = as_integer_t<elt_t, unsigned>;
    auto gold                 = w_t(1.61803398874989484820458683436563811772030917980575);
    auto goldbar              = w_t(-0.61803398874989484820458683436563811772030917980575);
    constexpr elt_t oneosqrt5 = 0.4472135954999579392818347337462552470881236719223;
    auto            nm1       = to_<eli_t>((n));
    auto            c2        = fms(gold, a, b) * oneosqrt5;
    auto            c1        = a - c2;
    auto            f         = fma(c1, pow(gold, nm1), c2 * pow(goldbar, nm1));
    return if_else(is_flint(a) && is_flint(b), nearest(f), f);
  }
  else return apply_over(fibonacci, n, a, b);
}
}
