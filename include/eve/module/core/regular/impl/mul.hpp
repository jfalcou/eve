//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once



#include <eve/concept/value.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T mul_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if constexpr (O::contains(saturated2) && integral_value<T>)
    {
      if constexpr (signed_integral_value<T>)
      {
        if constexpr(scalar_value<T>)
        {
          if constexpr (sizeof(T) <= 4)
          {
            using up_t = upgrade_t<T>;
            return static_cast<T>(saturate(static_cast<up_t>(a) * static_cast<up_t>(b), as<T>{}));
          }
          else if constexpr (sizeof(T) == 8)
          {
            using un_t = std::make_unsigned_t<T>;

            if( b == 0 || a == 0 ) return zero(as<T>{});

            T sgn = bit_xor(bitofsign(a), bitofsign(b));

            if (b == valmin(as<T>{}) || a == valmin(as<T>{}))
            {
              return sgn ? valmin(as<T>{}) : valmax(as<T>{});
            }

            un_t aa  = eve::abs(a);
            un_t bb  = eve::abs(b);
            
            auto aux = [sgn](const T& mini, const T& maxi, const un_t& amini, const un_t& amaxi)
            {
              un_t z = valmax(as<T>{}) / amaxi;
              return (z < amini) ? (sgn ? valmin(as<T>{}) : valmax(as<T>{})) : mini * maxi;
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
              using sup_t = upgrade_t<elt_t>;
              auto z      = mul(convert(a, as<sup_t>()), convert(b, as<sup_t>()));
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
      else //unsigned
      {
        if constexpr (scalar_value<T>)
        {
          if constexpr (sizeof(T) <= 4)
          {
            using up_t = upgrade_t<T>;
            up_t res   = up_t(a) * up_t(b);
            return (res > valmax(as<T>{})) ? valmax(as<T>{}) : static_cast<T>(res);
          }
          else
          {
            auto aux = [](const T& mini, const T& maxi)
            {
              T z = valmax(as<T>{}) / maxi;
              return (z < mini) ? valmax(as<T>{}) : mini * maxi;
            };

            if( b == 0 || a == 0 ) return zero(as<T>{});
            if( b >= a )           return aux(a, b);
            else                   return aux(b, a);
          }
        }
        else //simd
        {
          using elt_t = element_type_t<T>;
          if constexpr (sizeof(elt_t) <= 4)
          {
            using sup_t = upgrade_t<elt_t>;
            auto z      = mul(convert(a, as<sup_t>()), convert(b, as<sup_t>()));
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
    else
    {
      return a *= b;
    }
  }

  template<callable_options O, typename T, std::same_as<T>... Ts>
  EVE_FORCEINLINE constexpr T mul_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    //TODO: optimize, see add_
    r0   = mul[o](r0,r1);
    ((r0 = mul[o](r0,rs)),...);
    return r0;
  }
}
