//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>
#include <type_traits>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_andnot.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_odd.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/round.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <eve/module/core/regular/shr.hpp>


#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

namespace eve::detail
{

  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T div_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  {
    if constexpr(O::contains(saturated))
    {
      if constexpr( integral_value<T> )
      {
        EVE_ASSERT(eve::all((a != 0) || (b != 0)), "[eve] - div[saturated](0, 0) is undefined");
      }

      if constexpr( floating_value<T> )
      {
        return div[o.drop(saturated)](a, b);
      }
      else if constexpr( signed_integral_value<T> )
      {
        constexpr int shft = sizeof(element_type_t<T>) * 8 - 1;
        if constexpr( scalar_value<T> )
        {
          // case valmin/-1 is treated here
          if( b == -1 && a == eve::valmin(eve::as(a)) ) return eve::valmax(eve::as(a));
          if( b != 0 ) return div[o.drop(saturated)](a, b);
          // negative -> valmin,  positive -> valmax
          else return bit_xor(eve::valmax(eve::as(a)), shr(a, shft));
        }
        else if constexpr( simd_value<T> )
        {
          auto a2 = bit_xor(eve::valmax(eve::as(a)), shr(a, shft));
          // case valmin/-1 is treated here
          a           = inc[!(inc(b) | add(a, eve::valmin(eve::as(a))))](a);
          auto isnezb = is_nez(b);
          b           = if_else(isnezb, b, mone);
          return if_else(isnezb, div[o.drop(saturated)](a, b), a2);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        if constexpr( scalar_value<T> )
          return ( b != 0 ) ? a / b : valmax(as(a));
        else
          return if_else(is_nez(b), div(a, b), allbits);
      }
    }
    else if constexpr(O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      using elt_t = element_type_t<T>;

      if constexpr(floating_value<T>)
      {
        return round[o](div(a, b));
      }
      else if  constexpr(O::contains(downward))
      {
        EVE_ASSERT(eve::all((b != 0)), "[eve] - div[downward](a, 0) is undefined");
        if constexpr( signed_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            auto q    = div(a, b);
            auto r    = fms(q, b, a);
            auto test = if_else(is_ltz(b), is_ltz(r), is_gtz(r));
            return dec[test](q);
          }
          else
          {
            return convert[saturated](floor(convert(a, as<double>()) / convert(b, as<double>())), as<elt_t>());
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          return div(a, b);
        }
      }
      else if  constexpr(O::contains(toward_zero))
      {
        return div(a, b);
      }
      else if  constexpr(O::contains(upward) )
      {
        EVE_ASSERT(eve::all((b != 0)), "[eve] - div[upward](a, 0) is undefined");

        if constexpr( signed_value<T> )
        {
          if constexpr( std::is_same_v<elt_t, std::int64_t> )
          {
            auto q    = div(a, b);
            auto r    = fms(q, b, a);
            auto test = if_else(is_gtz(b), is_ltz(r), is_gtz(r));
            return inc[test](q);
          }
          else
          {
            return convert[saturated](ceil(convert(a,as<double>()) / convert(b,as<double>())), as<elt_t>());
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          auto q = div(a, b);
          return inc[is_nez(fms(q, b, a))](q);
        }
      }
      else if  constexpr(O::contains(to_nearest))
      {
        EVE_ASSERT(eve::all((b != 0)), "[eve] - div[to_nearest](a, 0) is undefined");

        using v_t = element_type_t<T>;

        if constexpr( sizeof(v_t) == 8 )
        {
          if constexpr( unsigned_value<T> )
          {
            auto q  = div(a, b);
            auto r1 = fnma(b, q, a);
            auto r2 = b - r1;

            return inc[(r1 > r2) || ((r1 == r2) && is_odd(q))](q);
          }
          else
          {
            auto ltza = is_ltz(a);
            a         = minus[ltza](a); // ensure a >= 0
            b         = minus[ltza](b);
            auto ltzb = is_ltz(b);
            auto q    = div(a, b);
            auto r1   = fnma(b, q, a);
            auto r2   = minus[ltzb](b) - r1;
            auto cond = (r1 > r2) || ((r1 == r2) && is_odd(q));
            
            return if_else(is_ltz(b), dec[cond](q), inc[cond](q));
          }
        }
        else
        {
          return convert[saturated](nearest(convert(a,as<double>()) / convert(b,as<double>())), as<v_t>());
        }
      }
    }
    else if constexpr (arithmetic_simd_value<T>)
    {
      // some div ops cannot be handled by some backends (e.g. arm/neon)
      apply<cardinal_t<T>::value>([&](auto... I) { (a.set(I, a.get(I) / b.get(I)), ...); });
      return a;
    }
    else
    {
      return a / b;
    }
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T div_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    auto that((r1 * (rs * ...)));
    if constexpr(std::is_integral_v<eve::element_type_t<T>>)
      EVE_ASSERT(eve::all(is_nez(that)), "[eve] div - 0/0 is undefined");
    return div[o](r0,that);
  }

  template<conditional_expr C, typename T, callable_options O>
  EVE_FORCEINLINE T  div_(EVE_REQUIRES(cpu_), C const& cond, O const & o, T t, T f) noexcept
  requires(integral_value<T>)
  {
    auto g = if_else(cond, f, one);
    return if_else(cond, eve::div[o.drop(condition_key)](t, g), t);
  }
}


#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
