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
  template<typename N, typename T, typename U, callable_options O>
  EVE_FORCEINLINE auto
  fibonacci_(EVE_REQUIRES(cpu_), O const&, N n, T a, U b) 
  {
    using c_t    = as_wide_as_t<common_value_t<T, U>, N>;
    using elt_t  = element_type_t<c_t>;
    using eli_t  = as_integer_t<elt_t, unsigned>;
    auto gold    = c_t(1.61803398874989484820458683436563811772030917980575);
    auto goldbar = c_t(-0.61803398874989484820458683436563811772030917980575);
    constexpr elt_t oneosqrt5 = 0.4472135954999579392818347337462552470881236719223;
    if constexpr(std::same_as<T, U>)
    {
      if constexpr( has_native_abi_v<T> &&  has_native_abi_v<N>)
      {
        auto nm1 = to_<eli_t>((n));
        auto c2  = fms(gold, a, b) * oneosqrt5;
        auto c1  = a - c2;
        auto f   = fma(c1, eve::pow(gold, nm1), c2 * eve::pow(goldbar, nm1));
        return  nearest[is_flint(a) && is_flint(b)](f);
      }
      else return apply_over(fibonacci, n, a, b);
    }
    else
      return indexed_call(fibonacci, n, a, b);
  }
}
