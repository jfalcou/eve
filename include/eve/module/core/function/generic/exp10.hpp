//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EXP10_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EXP10_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/invlog10_2.hpp>
#include <eve/constant/maxlog10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr T exp10_(EVE_SUPPORTS(cpu_)
                                     , D const &
                                     , T x) noexcept
  requires(contains<D>(types<regular_type, pedantic_type> {}))
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t =  element_type_t<T>;
      const T Log10_2hi =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      const T Log10_2lo =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
      auto xltminlog10 = x <  Minlog10(as(x));
      auto xgemaxlog10 = x >= Maxlog10(as(x));
      if constexpr(scalar_value<T>)
      {
        if (xgemaxlog10) return Inf(as(x));
        if (xltminlog10) return Zero(as(x));
      }
      auto c = nearest(Invlog10_2<T>()*x);
      auto k = c;
      x = fnma(c, Log10_2hi, x); //x-c*L
      x = fnma(c, Log10_2lo, x);
      if constexpr(std::is_same_v<elt_t, float>)
      {
        c = inc(horn<T, 0x40135d8e, 0x4029a926, 0x400237da, 0x3f95eb4c, 0x3f0aacef, 0x3e54dff1>(x)*x);
      }
      else if constexpr(std::is_same_v<elt_t, double>)
      {
        T xx = sqr(x);
        T px = x*horn<T, 0x40a2b4798e134a01ull, 0x40796b7a050349e4ull, 0x40277d9474c55934ull, 0x3fa4fd75f3062dd4ull> (xx);
        T x2 = px/(horn1<T, 0x40a03f37650df6e2ull, 0x4093e05eefd67782ull, 0x405545fdce51ca08ull> (xx)-px);
        c = inc(x2+x2);
      }
     auto z = D()(ldexp)(c, k);
      if constexpr(simd_value<T>)
      {
        z = if_else(xltminlog10, eve::zero_, z);
        z = if_else(xgemaxlog10, Inf(as(x)),z);
      }
      return z;
    }
    else return apply_over(exp10, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp10_(EVE_SUPPORTS(cpu_)
                                     , T const &x) noexcept
  {
      return exp10(regular_type(), x);
  }
}

#endif
