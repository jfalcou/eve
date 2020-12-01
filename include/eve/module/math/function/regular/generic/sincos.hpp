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
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fnms.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>
#include <utility>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sincos_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); // 0.61685027506808491367715568749226
                                                                            // but rounded upward
      auto x2          = sqr(a0);
      auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
      if constexpr( scalar_value<T> )
      {
        return (x2nlepi2_16) ? std::make_tuple(nan(eve::as<T>()), nan(eve::as<T>()))
                             : std::make_tuple(sin_eval(x2, a0), cos_eval(x2));
      }
      else
      {
        x2 = if_else(x2nlepi2_16, eve::allbits, x2);
        return std::make_tuple(sin_eval(x2, a0), cos_eval(x2));
      }
    }
    else
      return apply_over2(restricted(sincos), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sincos_(EVE_SUPPORTS(cpu_), small_type const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto reduce =  [](auto x)
      {
        auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
        auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
        auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();

        T xr = x-pio2_1;
        xr -= pio2_2;
        xr -= pio2_3;

        return xr;
      };

      T x = eve::abs(a0);

      if constexpr(scalar_value<T>)
      {
        using i_t =  as_integer_t<T, signed>;

        if (is_less_equal(x, eps(as<T>())))       return std::make_tuple(a0, one(eve::as<T>()));
        if (is_not_less_equal(x, pio_2(eve::as<T>()))) return std::make_tuple(nan(eve::as<T>()), nan(eve::as<T>()));

        i_t n = x > pio_4(eve::as<T>());

        if (n)
        {
          auto xr =  reduce(x);
          return std::make_tuple(bit_xor(bitofsign(a0), cos_eval(sqr(xr)))
                                , bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T)*8-1)));
        }
        else
        {
          return std::make_tuple(sin_eval(sqr(x), a0), cos_eval(sqr(x)));
        }
      }
      else
      {
        x = if_else(is_not_less_equal(x, pio_2(eve::as<T>())), eve::allbits, x);
        auto test = is_not_less_equal(x, pio_4(eve::as<T>()));
        auto n = binarize(test);
        auto xr =  if_else(test, reduce(x), x);
        return  sincos_finalize(a0, n, xr, T(0));
      }
    }
    else
    {
      return apply_over2(small(sincos), a0);
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  /// big medium
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto sincos_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
        if( is_not_finite(a0) )
          return std::make_tuple(nan(eve::as<T>()), nan(eve::as<T>()));
      const T x          = abs(a0);
      auto [fn, xr, dxr] = D()(rempio2)(x);
      return sincos_finalize(bitofsign(a0), fn, xr, dxr);
    }
    else
    {
      return apply_over2(D()(sincos), a0);
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sincos_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( all(x <= pio_4(eve::as(x))) )
        return restricted(sincos)(a0);
      else if( all(x <= pio_2(eve::as(x))) )
        return small(sincos)(a0);
      else if( all(x <= Rempio2_limit(medium_type(), as(a0))) )
        return medium(sincos)(a0);
      else
        return big(sincos)(a0);
    }
    else
    {
      return apply_over2(sincos, a0);
    }
  }
}

