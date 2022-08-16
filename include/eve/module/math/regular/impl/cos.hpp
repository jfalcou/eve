//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/atan2.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/sincos.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cos_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x2          = sqr(a0);
    auto x2nlepi2_16 = is_not_less_equal(x2, upward(pi2o_16)(as(a0)));
    if constexpr( scalar_value<T> ) return (x2nlepi2_16) ? nan(eve::as<T>()) : cos_eval(x2);
    else return if_else(x2nlepi2_16, eve::allbits, cos_eval(x2));
  }
  else return apply_over(quarter_circle(cos), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cos_(EVE_SUPPORTS(cpu_), half_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    T    x        = eve::abs(a0);
    auto xnlepio2 = is_not_less_equal(x, pio_2(eve::as<T>()));
    if constexpr( scalar_value<T> )
      if( xnlepio2 ) return nan(eve::as<T>());
    auto reduce = [](auto x)
    {
      auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
      auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
      auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
      auto xr     = x - pio2_1;
      xr -= pio2_2;
      xr -= pio2_3;
      return xr;
    };
    if constexpr( scalar_value<T> )
    {
      using i_t = as_integer_t<T, signed>;
      i_t n     = x > pio_4(eve::as<T>());
      if( n )
      {
        auto xr = reduce(x);
        return bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1));
      }
      else return cos_eval(sqr(x));
    }
    else
    {
      using elt_t   = element_type_t<T>;
      auto n        = binarize(is_not_less_equal(x, pio_4(eve::as(x))));
      auto sign_bit = binarize(is_nez(n), signmask(eve::as<elt_t>()));
      auto xr       = reduce(x);
      xr            = if_else(n, xr, x);
      auto z        = sqr(xr);
      auto se       = bit_xor(sin_eval(z, xr), sign_bit);
      auto ce       = cos_eval(z);
      auto z1       = if_else(n, se, ce);
      return if_else(xnlepio2, eve::allbits, z1);
    }
  }
  else return apply_over(half_circle(cos), a0);
}

//   template<decorator D, floating_real_value T>
//   EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_), full_circle_type const &, T a0)
//   noexcept
//   {
//     if constexpr( has_native_abi_v<T> )
//     {
//       auto x         = abs(a0);
//       auto xnlelim   = is_not_less_equal(x, Rempio2_limit(full_circle_type(), as(a0)));
//       if constexpr( scalar_value<T> )
//       {
//         if( xnlelim ) return nan(eve::as<T>());
//       }
//       else
//         x = if_else(xnlelim, allbits, x);
//       auto [fn, xr, dxr] = full_circle(rempio2)(x);
//       return cos_finalize(fn, xr, dxr);
//     }
//     else
//       return apply_over(full_circle(cos), a0);
//   }

template<decorator D, floating_real_value T>
EVE_FORCEINLINE constexpr auto
cos_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<full_circle_type, medium_type, big_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x       = abs(a0);
    auto xnlelim = is_not_less_equal(x, Rempio2_limit(D(), as(a0)));
    if constexpr( scalar_value<T> )
    {
      if( xnlelim ) return nan(eve::as<T>());
    }
    else x = if_else(xnlelim, allbits, x);
    auto [fn, xr, dxr] = D()(rempio2)(x);
    return cos_finalize(fn, xr, dxr);
  }
  else return apply_over(D()(cos), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cos_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(x <= Rempio2_limit(quarter_circle_type(), as(a0))) )
      return quarter_circle(cos)(a0);
    else if( eve::all(x <= Rempio2_limit(half_circle_type(), as(a0))) ) return half_circle(cos)(a0);
    else if( eve::all(x <= Rempio2_limit(full_circle_type(), as(a0))) ) return full_circle(cos)(a0);
    else if( eve::all(x <= Rempio2_limit(medium_type(), as(a0))) ) return medium(cos)(a0);
    else return big(cos)(a0);
  }
  else return apply_over(cos, a0);
}


// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cos_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cos, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cos_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cos), t);
}
}
