//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cfenv>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/two_prod.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/prev.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/traits/updown.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr auto mul_(EVE_REQUIRES(cpu_), O const& opts, T a, U b) noexcept
  {
    if constexpr(O::contains(widen))
    {
      return mul[opts.drop(widen)](upgrade(a), upgrade(b));
    }
    else    if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper) ))
    {
      if constexpr(O::contains(strict))
      {
        auto r = mul[opts.drop(lower, upper, strict)](a, b);
        if constexpr(O::contains(lower))
          return prev(r);
        else
          return next(r);
      }
      else
      {
        auto [r, e] = eve::two_prod(a, b);
        if constexpr(O::contains(lower))
          return eve::prev[eve::is_ltz(e)](r);
        else
          return eve::next[eve::is_gtz(e)](r);
      }
    }
    else if constexpr (plain_scalar_value<T> && simd_value<U>)
    {
      // some backends are optimized for this specific case, let them have
      // a chance to handle it
      return mul[opts](b, a);
    }
    else if constexpr (simd_value<T> && plain_scalar_value<U>)
    {
      return mul[opts](a, T{b});
    }
    else if (std::is_same_v<T, U>)
    {
      if constexpr (O::contains(saturated) && integral_value<T>)
      {
        if constexpr (signed_integral_value<T>)
        {
          if constexpr(scalar_value<T>)
          {
            if constexpr (sizeof(T) <= 4)
            {
              using upw_t = upgrade_t<T>;
              return static_cast<T>(saturate(static_cast<upw_t>(a) * static_cast<upw_t>(b), as<T>{}));
            }
            else if constexpr (sizeof(T) == 8)
            {
              using un_t = std::make_unsigned_t<T>;

              if ((b == 0) || (a == 0)) return zero(as<T>{});

              T sgn = bit_xor(bitofsign(a), bitofsign(b));

              if ((b == valmin(as<T>{})) || (a == valmin(as<T>{})))
              {
                return sgn ? valmin(as<T>{}) : valmax(as<T>{});
              }

              un_t aa  = eve::abs(a);
              un_t bb  = eve::abs(b);

              auto aux = [sgn](const T& mni, const T& mxi, const un_t& amini, const un_t& amaxi)
              {
                un_t z = valmax(as<T>{}) / amaxi;
                return (z < amini) ? (sgn ? valmin(as<T>{}) : valmax(as<T>{})) : mni * mxi;
              };

              if( bb >= aa ) return aux(a, b, aa, bb);
              else           return aux(b, a, bb, aa);
            }
          }
          else // simd
          {
            using elt_t = element_type_t<T>;
            if constexpr (floating_value<T>)
            {
              return a * b;
            }
            else if constexpr (integral_value<T>)
            {
              if constexpr (sizeof(elt_t) <= 4)
              {
                using supw_t = upgrade_t<elt_t>;
                auto z      = mul(convert(a, as<supw_t>()), convert(b, as<supw_t>()));
                auto s      = saturate(z, as<elt_t>());
                return convert(s, as<elt_t>());
              }
              else
              {
                auto that = map(eve::mul[saturated], a, b);
                return that;
              }
            }
          }
        }
        else // unsigned
        {
          if constexpr (scalar_value<T>)
          {
            if constexpr (sizeof(T) <= 4)
            {
              using upw_t = upgrade_t<T>;
              upw_t res   = upw_t(a) * upw_t(b);
              return (res > valmax(as<T>{})) ? valmax(as<T>{}) : static_cast<T>(res);
            }
            else
            {
              auto aux = [](const T& mni, const T& mxi)
              {
                T z = valmax(as<T>{}) / mxi;
                return (z < mni) ? valmax(as<T>{}) : mni * mxi;
              };

              if( b == 0 || a == 0 ) return zero(as<T>{});
              if( b >= a )           return aux(a, b);
              else                   return aux(b, a);
            }
          }
          else // simd
          {
            using elt_t = element_type_t<T>;
            if constexpr (sizeof(elt_t) <= 4)
            {
              using supw_t = upgrade_t<elt_t>;
              auto z      = mul(convert(a, as<supw_t>()), convert(b, as<supw_t>()));
              auto s      = saturate(z, as<elt_t>());
              return convert(s, as<elt_t>());
            }
            else
            {
              auto that = map(eve::mul[saturated], a, b);
              return that;
            }
          }
        }
      }
      else if constexpr (arithmetic_simd_value<T>)
      {
        // some mul ops cannot be handled by the neon backend
        apply<cardinal_t<T>::value>([&](auto... I) { (a.set(I, a.get(I) * b.get(I)), ...); });
        return a;
      }
      else
      {
        return a * b;
      }
    }
  }

  template<callable_options O, typename T, typename U, typename... Vs>
  EVE_FORCEINLINE constexpr auto mul_(EVE_REQUIRES(cpu_), O const & o, T r0, U r1, Vs... rs) noexcept
  {
    //TODO: optimize, see add_
    if constexpr(O::contains(widen))
      return mul[o.drop(widen)](upgrade(r0), upgrade(r1), upgrade(rs)...);
    else
    {
      r0   = mul[o](r0,r1);
      ((r0 = mul[o](r0,rs)),...);
      return r0;
    }
  }
}
