//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<scalar_value I, floating_scalar_value T>
  EVE_FORCEINLINE T tchebytchev_u_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    EVE_ASSERT(is_gez(n), "n is not positive");
    EVE_ASSERT(is_flint(n), "n is not flint");
    switch (int(n)){
    case 0  :return one(as(x));
    case 1  :return x;
    case 2  :return fma(x, x+x, mone(as(x)));
    case 3  :return x*(4*sqr(x)-3);
    case 4  :return inc(8*sqr(x)*(sqr(x)-1));
    default :
      auto nn = T(n);
      auto z =  eve::abs(x);
      if ( z <= one(as(z)))
        return cos(nn*acos(x));
      else
      {
        auto t = cosh(nn*acosh(z));
        return is_gez(x) ? t :t*sign_alternate(nn);
      }
    }
  }

  template<scalar_value I, floating_simd_value T>
  EVE_FORCEINLINE T tchebytchev_u_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    EVE_ASSERT(is_gez(n), "n is not positive");
    EVE_ASSERT(is_flint(n), "n is not flint");
    if constexpr(has_native_abi_v<T>)
    {
      switch (int(n)){
      case 0  :return one(as(x));
      case 1  :return 2*x;
      case 2  :return fms(4*x, x, 1);
      case 3  :return 4*x*fms(2*x, x, 1);
      case 4  :return inc(4*sqr(x)*(fms(2*x, 2*x, 3)));
      default :
        auto nn = inc(convert(n, as<element_type_t<T>>()));
        auto z =  eve::abs(x);
        auto acx = acos(x);

        auto r0 = sin(nn*acx)/sin(acx);
        auto r = if_else((1-z < eps(as(x))
                         , if_else(is_gez(x), nn, nn*alternate_sign(n))
                         , r0)
                        );
    auto test = z <= one(as(z));
    if (all(test))
    {
      return r;
    }
    else
    {
      auto achx = acosh(x);
      auto t0 = sinh(n*achx)/sinh(achx);
      auto t = if_else((z-1 < eps(as(x))
                       , if_else(is_gez(x), nn, nn*alternate_sign(n))
                       , t0)
                      );
      return if_else(test,  r, if_else(is_gez(x), t, t*sign_alternate(nn)));
    }
    }
    else return apply_over(tchebytchev_u, n, x);
  }

//   template<simd_value I, floating_real_value T>
//   EVE_FORCEINLINE auto tchebytchev_u_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
//   //  requires(index_compatible < I, T>
//   {
//     if constexpr(has_native_abi_v<T> && has_native_abi_v<I>)
//     {
//       EVE_ASSERT(eve::all(is_gez(n)), "some elements of n are not positive");
//       EVE_ASSERT(eve::all(is_flint(n)), "some elements of n are not flint");
//       auto nn = convert(n, as<eve::element_type_t<T>>());
//       auto z =  eve::abs(x);
//       auto r = cos(nn*acos(x));
//       auto test = z <= one(as(z));
//       if (all(test)) return r;
//       else
//       {
//         auto t = cosh(nn*acosh(z));
//         return if_else(test,  r, if_else(is_gez(x), t, t*sign_alternate(nn)));
//       }
//     }
//     else return apply_over(tchebytchev_u, n, x);
//   }


//   template<integral_simd_value I, floating_real_value T>
//   EVE_FORCEINLINE auto tchebytchev_u_(EVE_SUPPORTS(cpu_), kind_2_type const &, I n, T x) noexcept
//   {
//     EVE_ASSERT(eve::all(is_gez(n)), "some elements of n are not positive");
//     auto nn = inc(convert(n, as<element_type_t<T>>()));
//     auto z =  eve::abs(x);
//     auto acx = acos(x);

//     auto r0 = sin(nn*acx)/sin(acx);
//     auto r = if_else((1-z < eps(as(x))
//                      , if_else(is_gez(x), nn, nn*alternate_sign(n))
//                      , r0)
//                     );
//     auto test = z <= one(as(z));
//     if (all(test))
//     {
//       return r;
//     }
//     else
//     {
//       auto achx = acosh(x);
//       auto t0 = sinh(n*achx)/sinh(achx);
//       auto t = if_else((z-1 < eps(as(x))
//                        , if_else(is_gez(x), nn, nn*alternate_sign(n))
//                        , t0)
//                       );
//       return if_else(test,  r, if_else(is_gez(x), t, t*sign_alternate(nn)));
//     }
//   }

}
