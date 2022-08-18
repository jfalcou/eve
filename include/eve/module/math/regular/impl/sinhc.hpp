//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sinhc_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_eqz(a0) ) return one(eve::as(a0));
      if constexpr( eve::platform::supports_infinites )
        if( is_infinite(a0) ) return zero(eve::as<T>());
      if constexpr( eve::platform::supports_denormals )
        return eve::abs(a0) < eps(as<T>()) ? one(eve::as<T>()) : sinh(a0) / a0;
      else return sinh(a0) / a0;
    }
    else
    {
      auto sinhc_kernel = [](auto x2)
      {
        using elt_t = element_type_t<T>;
        if constexpr( std::is_same_v<elt_t, float> )
        {
          return horn<T,
                      0x3f800000, // 1.0f
                      0x3e2aaacc, // 1.66667160211E-1f
                      0x3c087bbe, // 8.33028376239E-3f
                      0x39559e2f  // 2.03721912945E-4f
                      >(x2);
        }
        else
        {
          return inc(
              x2
              * horn<T,
                     0xc115782bdbf6ab05ull, //  -3.51754964808151394800E5
                     0xc0c694b8c71d6182ull, //  -1.15614435765005216044E4,
                     0xc064773a398ff4feull, //  -1.63725857525983828727E2,
                     0xbfe9435fe8bb3cd6ull  //  -7.89474443963537015605E-1
                     >(x2)
              / horn1<T,
                      0xc1401a20e4f90044ull, //  -2.11052978884890840399E6
                      0x40e1a7ba7ed72245ull, //   3.61578279834431989373E4,
                      0xc0715b6096e96484ull  //  -2.77711081420602794433E2,
                                            //  0x3ff0000000000000ull  //   1.00000000000000000000E0
                      >(x2));
        }
      };

      T    x   = abs(a0);
      auto lt1 = is_less(x, one(eve::as<T>()));
      auto nb  = eve::count_true(lt1);
      T    z   = zero(eve::as<T>());
      if( nb > 0 )
      {
        z = sinhc_kernel(sqr(x));
        if( nb >= T::size() ) return z;
      }
      auto test1 = is_greater(x, maxlog(eve::as<T>()) - log_2(eve::as<T>()));
      T    fac   = if_else(test1, half(eve::as<T>()), one(eve::as<T>()));
      T    tmp   = exp(x * fac);
      T    tmp1  = (half(eve::as<T>()) * tmp) / x;
      T    r     = if_else(test1, tmp1 * tmp, average(tmp, -rec(tmp)) / x);
      if constexpr( eve::platform::supports_infinites ) r = if_else(x == inf(eve::as<T>()), x, r);
      return if_else(lt1, z, r);
    }
  }
  else { return apply_over(sinhc, a0); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sinhc_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::sinhc, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
sinhc_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::sinhc), t);
}
}
