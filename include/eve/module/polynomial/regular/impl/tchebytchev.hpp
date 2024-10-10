//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{
  // Recurrence relation for Tchebytchev polynomials:
  template<callable_options O, typename T>
  requires(O::contains(successor))
  constexpr EVE_FORCEINLINE T
  tchebytchev_(EVE_REQUIRES(cpu_),  O const& , T x, T tn, T tnm1)
  {
    return fms(x + x, tn, tnm1);
  }

  //  Tchebytchev bases of first and second kind:
  template<callable_options O, typename I, typename T>
  constexpr as_wide_as_t<T, I>
  tchebytchev_(EVE_REQUIRES(cpu_),  O const& o, I n, T x)
  {
    EVE_ASSERT(eve::all(is_gez(n)), "n  not positive");
    EVE_ASSERT(eve::all(is_flint(n)), "n  not flint");
    using r_t = as_wide_as_t<T, I>;
    if constexpr(O::contains(kind_1))
    {
      if constexpr(scalar_value<I>)
      {
        if constexpr(scalar_value<T>)
        {
          switch( int(n) )
          {
          case 0: return one(as{x});
          case 1: return x;
          case 2: return fma(x, x + x, mone(as{x}));
          case 3: return x * (4 * sqr(x) - 3);
          case 4: return inc(8 * sqr(x) * (sqr(x) - 1));
          default:
            auto nn = T(n);
            auto z  = eve::abs(x);
            if( z <= one(as{z}) ) return cos(nn * acos(x));
            else
            {
              auto t = cosh(nn * acosh(z));
              return is_gez(x) ? t : t * sign_alternate(nn);
            }
          }
        }
        else
        {
          if constexpr( has_native_abi_v<T> )
          {
            switch( int(n) )
            {
            case 0: return one(as{x});
            case 1: return x;
            case 2: return fma(x, x + x, mone(as{x}));
            case 3: return x * fms(4 * x, x, 3);
            case 4: return inc(8 * sqr(x) * (sqr(x) - 1));
            default:
              auto nn   = T(n);
              auto z    = eve::abs(x);
              auto test = (z <= one(as{z}));
              if( all(test) ) return cos(nn * acos(x));
              else
              {
                auto t = cosh(nn * acosh(z));
                if( none(test) ) return if_else(is_gez(x), t, t * sign_alternate(nn));
                else
                {
                  auto r0 = cos(nn * acos(x));
                  auto r1 = if_else(is_gez(x), t, t * sign_alternate(nn));
                  return if_else(test, r0, r1);
                }
              }
            }
          }
          else return apply_over(tchebytchev, n, x);
        }
      }
      else if constexpr(simd_value<I>)
      {
        if constexpr( scalar_value<T>)
        {
          return tchebytchev[o](n, r_t(x));
        }
        else if constexpr( has_native_abi_v<T> )
        {
          auto nn   = convert(n, as<eve::element_type_t<T>>{});
          auto z    = eve::abs(x);
          auto r    = cos(nn * acos(x));
          auto test = z <= one(as{z});
          if( all(test) ) return r;
          else
          {
            auto t = cosh(nn * acosh(z));
            return if_else(test, r, if_else(is_gez(x), t, t * sign_alternate(nn)));
          }
        }
        else return apply_over(tchebytchev, n, x);
      }
    }
    else if constexpr(O::contains(kind_2))
    {
      auto nn  = inc(convert(n, as_element(x)));
      auto z   = eve::abs(x);
      auto acx = acos(x);

      auto r0   = sin(nn * acx) / sin(acx);
      auto r    = if_else(oneminus(z) < eps(as{x}), if_else(is_gez(x), nn, -nn * sign_alternate(nn)), r0);
      auto test = z <= one(as{z});
      if( all(test) )
      {
        return r;
      }
      else
      {
        auto achx = acosh(x);
        auto t0   = sinh(nn * achx) / sinh(achx);
        auto t    = if_else(dec(z) < eps(as{x}), if_else(is_gez(x), nn, -nn * sign_alternate(nn)), t0);
        return if_else(test, r, if_else(is_gez(x), t, -t * sign_alternate(nn)));
      }
    }
    else
    {
      return tchebytchev[kind_1](n, x);
    }
  }
}
