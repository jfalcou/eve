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
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/ceil.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_odd.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/saturate.hpp>

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T div_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if constexpr( integral_value<T>)
    {
      if constexpr(!O::contains(saturated2))
        EVE_ASSERT(eve::all(is_nez(b)), "[eve::div] for integral types non masked elements of the second parameter must be non zero");
      using elt_t = element_type_t<T>;
      if constexpr(O::contains(downward2))
      {
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
            return saturated(convert)(floor(convert(a, as<double>()) / convert(b, as<double>())), as<elt_t>());
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          return div(a, b);
        }
      }
      else if constexpr(O::contains(upward2))
      {
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
            return saturated(convert)(ceil(convert(a,as<double>()) / convert(b,as<double>())), as<elt_t>());
          }
        }
        else if constexpr( unsigned_value<T> )
        {
          auto q = div(a, b);
          return inc[is_nez(fms(q, b, a))](q);
        }
      }
      else if constexpr(O::contains(to_nearest2))
      {
        if constexpr( sizeof(elt_t) == 8 )
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
          return saturated(convert)(nearest(convert(a,as<double>()) / convert(b,as<double>())), as<elt_t>());
        }
      }
      else if constexpr(O::contains(saturated2))
      {
        EVE_ASSERT(eve::all((a != 0) || (b != 0)), "[eve] - saturated(div)(0, 0) is undefined");
        if constexpr( signed_integral_value<T> )
        {
          constexpr int shft = sizeof(element_type_t<T>) * 8 - 1;
          if constexpr(scalar_value<T>)
          {
            if constexpr( scalar_value<T> )
            {
              // case valmin/-1 is treated here
              if( b == -1 && a == eve::valmin(eve::as(a)) ) return eve::valmax(eve::as(a));
              if( b != 0 ) return div(a, b);
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
              return if_else(isnezb, div(a, b), a2);
            }
          }
          else // simd
          {
            auto a2 = bit_xor(eve::valmax(eve::as(a)), shr(a, shft));
            // case valmin/-1 is treated here
            a           = inc[!(inc(b) | add(a, eve::valmin(eve::as(a))))](a);
            auto isnezb = is_nez(b);
            b           = if_else(isnezb, b, mone);
            return if_else(isnezb, div(a, b), a2);
          }
        }
        else //unsigned
        {
          auto inzb = is_nez(b);
          if constexpr(scalar_value<T>)
          {
            return ( inzb ) ? div[inzb](a, b) : eve::valmax(as(a));
          }
          else //simd
          {
            return if_else(inzb, div[inzb](a, b), allbits);
          }
        }
      }
      else
        return a /= b;
    }
    else
    {
      return a /= b;
    }
  }

  //masked call must treat specifically masked 0 denominateur
  template<conditional_expr C, integral_value T, callable_options O>
  EVE_FORCEINLINE auto
  div_(EVE_REQUIRES(cpu_), C const& cond, O const& o, T const& t, T const& f) noexcept
  {
    auto g = if_else(cond, f, mone);
    return if_else(cond, div[o.drop(condition_key)](t, g), t);
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T div_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    if constexpr(sizeof...(rs) == 0)
    {
      return div[o](r0, r1);
    }
    else
    {
      auto that(mul(r1, rs...));
      if constexpr(integral_value<T>)
        EVE_ASSERT(eve::all(is_nez(that)), "[eve] div - 0/0 is undefined");
      return div[o](r0, that);
    }
  }
}

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
