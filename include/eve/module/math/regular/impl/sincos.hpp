//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sincos_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto pi2_16 = pi2o_16[upward](as<T>());
    auto x2          = sqr(a0);
    auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
    if constexpr( scalar_value<T> )
    {
      return (x2nlepi2_16) ? kumi::tuple<T, T> {nan(eve::as<T>()), nan(eve::as<T>())}
                           : kumi::tuple<T, T> {sin_eval(x2, a0), cos_eval(x2)};
    }
    else
    {
      x2 = if_else(x2nlepi2_16, eve::allbits, x2);
      return {sin_eval(x2, a0), cos_eval(x2)};
    }
  }
  else return apply_over2(quarter_circle(sincos), a0);
}

template<floating_ordered_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sincos_(EVE_SUPPORTS(cpu_), half_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto reduce = [](auto x)
    {
      auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
      auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
      auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});

      T xr = x - pio2_1;
      xr -= pio2_2;
      xr -= pio2_3;

      return xr;
    };

    T x = eve::abs(a0);

    if constexpr( scalar_value<T> )
    {
      using i_t = as_integer_t<T, signed>;

      if( is_less_equal(x, eps(as<T>())) ) return {a0, one(eve::as<T>())};
      if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return {nan(eve::as<T>()), nan(eve::as<T>())};

      i_t n = x > pio_4(eve::as<T>());

      if( n )
      {
        auto xr = reduce(x);
        return {bit_xor(bitofsign(a0), cos_eval(sqr(xr))),
                bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1))};
      }
      else { return {sin_eval(sqr(x), a0), cos_eval(sqr(x))}; }
    }
    else
    {
      x           = if_else(is_not_less_equal(x, pio_2(eve::as<T>())), eve::allbits, x);
      auto test   = is_not_less_equal(x, pio_4(eve::as<T>()));
      auto n      = binarize(test);
      auto xr     = if_else(test, reduce(x), x);
      auto [s, c] = sincos_finalize(a0, n, xr, T(0));
      return {s, c};
    }
  }
  else { return apply_over2(half_circle(sincos), a0); }
}

template<decorator D, floating_ordered_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sincos_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<full_circle_type, medium_type, big_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x       = abs(a0);
    auto xnlelim = is_not_less_equal(x, Rempio2_limit(D(), as(a0)));
    if constexpr( scalar_value<T> )
    {
      if( xnlelim ) return {nan(eve::as<T>()), nan(eve::as<T>())};
    }
    else x = if_else(xnlelim, allbits, x);
    auto [fn, xr, dxr] = D()(rempio2)(x);
    auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
    return {s, c};
  }
  else { return apply_over2(D()(sincos), a0); }
}

template<typename T>
EVE_FORCEINLINE constexpr auto
sincos_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(x <= Rempio2_limit(quarter_circle_type(), as(a0))) )
      return quarter_circle(sincos)(a0);
    else if( eve::all(x <= Rempio2_limit(half_circle_type(), as(a0))) )
      return half_circle(sincos)(a0);
    else if( eve::all(x <= Rempio2_limit(full_circle_type(), as(a0))) )
      return full_circle(sincos)(a0);
    else if( eve::all(x <= Rempio2_limit(medium_type(), as(a0))) ) return medium(sincos)(a0);
    else return big(sincos)(a0);
  }
  else return apply_over2(sincos, a0);
}
}
