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
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/logical_ornot.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_),
                         to_nearest_type const &,
                         T const &a,
                         T const &b) noexcept requires has_native_abi_v<T>
  {
    using elt_t = element_type_t<T>;
    if constexpr( floating_real_value<T> )
    {
      return nearest(div(a, b));
    }
    else if constexpr( integral_real_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if constexpr( signed_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            using ui_t = as_integer_t<T, unsigned>;
            if( !a )
              return Zero<T>();
            if( b )
            {
              ui_t aa = saturated_(eve::abs)(a);
              ui_t ab = saturated_(eve::abs)(b);
              T    q  = to_nearest_(div)(aa, ab);
              return if_else(is_gez(a ^ b), q, -q);
            }
            else
              return ((a > 0) ? Valmax<T>() : Valmin<T>());
          }
          else
          {
            using f_t = as_floating_point_t<elt_t>;
            if( b )
              return saturated_(convert)(nearest(static_cast<f_t>(a) / static_cast<f_t>(b)),
                                         as<T>());
            else
              return (a) ? ((a > 0) ? Valmax<T>() : Valmin<T>()) : Zero<T>();
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          if( b )
          {
            T q   = div(a, b);
            T rx2 = 2 * (a - q * b);
            if( rx2 >= b )
            {
              if( (rx2 == b) && is_even(q) )
                --q;
              ++q;
            }
            return q;
          }
          else
            return bit_mask(a);
        }
      }
      else if constexpr( simd_value<T> )
      {
        if constexpr( signed_integral_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            auto aa  = saturated_(eve::abs)(a);
            auto bb  = saturated_(eve::abs)(b);
            bb       = if_else(is_eqz(bb), eve::allbits, bb);
            auto q   = eve::saturated_(eve::div)(aa, bb);
            auto rx2 = 2 * (aa - q * bb);
            q = if_else(is_greater_equal(rx2, bb), inc[logical_ornot(rx2 != bb, is_even(q))](q), q);
            return if_else(
                is_nez(b),
                if_else(is_gez(a ^ b), q, -q),
                if_else(is_eqz(a), eve::zero_, if_else(is_gtz(a), Valmax<T>(), Valmin<T>())));
          }
          else
          {
            return if_else(
                is_nez(b),
                saturated_(convert)(nearest(double_(a) / double_(b)), as<elt_t>()),
                if_else(is_eqz(a), eve::zero_, if_else(is_gtz(a), Valmax<T>(), Valmin<T>())));
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          auto bb  = if_else(is_eqz(b), eve::allbits, b);
          T    q   = div(a, bb);
          T    rx2 = 2 * (a - q * bb);
          q = if_else(is_greater_equal(rx2, bb), inc[logical_ornot(rx2 != bb, is_even(q))](q), q);
          return if_else(is_nez(b), q, bit_mask(a));
        }
      }
    }
  } 
}
