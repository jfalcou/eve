//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/detail/scalar/rempio2_kernel.hpp>
#include <eve/module/math/detail/simd/rempio2_kernel.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); // 0.61685027506808491367715568749226
                                                                            // but rounded upward
      auto x2 = sqr(a0);
      if constexpr( scalar_value<T> )
        if( is_not_less_equal(x2, pi2_16) )
          return Nan<T>();
      auto x = eve::abs(a0);
      auto r = bit_xor(detail::sin_eval(x2, x), bitofsign(a0));
      if constexpr( scalar_value<T> )
        return r;
      else
        return if_else(is_not_less_equal(x2, pi2_16), eve::allbits_, r);
    }
    else
      return apply_over(restricted_(sin), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_), small_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto reduce = [](auto x) {
        auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
        auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
        auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
        T    xr     = x - pio2_1;
        xr -= pio2_2;
        xr -= pio2_3;
        return xr;
      };
      T x = eve::abs(a0);
      if constexpr( scalar_value<T> )
      {
        using i_t = as_integer_t<T, signed>;
        if( is_less_equal(x, Eps<T>()) )
          return a0;
        if( is_not_less_equal(x, Pio_2<T>()) )
          return Nan<T>();
        i_t n = x > Pio_4<T>();
        if( n )
        {
          auto xr = reduce(x);
          return bit_xor(bitofsign(a0), cos_eval(sqr(xr)));
        }
        else
          return sin_eval(sqr(x), a0);
      }
      else
      {
        auto n     = is_not_less_equal(x, Pio_4<T>());
        auto xr    = reduce(x);
        xr         = if_else(n, xr, x);
        const T z  = sqr(xr);
        const T se = sin_eval(z, xr);
        const T ce = cos_eval(z);
        const T z1 = bit_xor(bitofsign(a0), if_else(n, ce, se));
        return if_else(is_not_less_equal(x, Pio_2<T>()), Nan<T>(), z1);
      }
    }
    else
      return apply_over(small_(sin), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
        if( is_not_finite(a0) )
          return Nan<T>();
      auto x             = abs(a0);
      auto [fn, xr, dxr] = D()(rempio2)(x);
      return sin_finalize(bitofsign(a0), fn, xr, dxr);
    }
    else
      return apply_over(D()(sin), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( all(x <= Pio_4(as(x))) )
        return restricted_(sin)(a0);
      else if( all(x <= Pio_2(as(x))) )
        return small_(sin)(a0);
      else if( all(x <= Rempio2_limit(medium_type(), as(a0))) )
        return medium_(sin)(a0);
      else
        return big_(sin)(a0);
    }
    else
      return apply_over(sin, a0);
  }

}

