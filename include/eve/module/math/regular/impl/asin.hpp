//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/branch.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>

namespace eve::detail
{

  template<floating_ordered_value T>
  EVE_FORCEINLINE auto
  asin_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      auto x      = eve::abs(a0);
      auto sgn    = eve::bitofsign(a0);
      if constexpr( std::is_same_v<elt_t, float> )
      {
        const auto x_larger_05 = x > half(eve::as<T>());
        T          z           = if_else(x_larger_05, half(eve::as<T>()) * oneminus(x), eve::sqr(x));
        x                      = if_else(x_larger_05, sqrt(z), x);
        T z1 =
          eve::reverse_horner(z, T(0x1.5555c8p-3f), T(0x1.3301ecp-4f), T(0x1.747d8ep-5f)
                             , T(0x1.8c2fc6p-6f), T(0x1.5966a4p-5f));
        ;
        z1   = fma(z1, z * x, x);
        z    = if_else(x_larger_05, pio_2(eve::as<T>()) - (z1 + z1), z1);
        return eve::bit_xor(z, sgn);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        auto small = x < sqrteps(eve::as<T>());
        if constexpr( scalar_value<T> ) // early scalar return
        {
          if( small ) return a0;
          if( (x > one(eve::as<T>())) ) return nan(eve::as<T>());
        }
        else if constexpr( simd_value<T> ) // simd preparation
        {
          x = if_else(x > one(eve::as<T>()), eve::allbits, x);
        }
        auto case_1 = [](const T& x) { // x < 0.625
          auto zz1 = eve::oneminus(x);
          auto num = zz1
          *
          eve::reverse_horner(zz1, T(0x1.c896240f3081dp+4), T(-0x1.991aaac01ab68p+4), T(0x1.bdff5baf33e6ap+2), T(-0x1.2079259f9290fp-1), T(0x1.84fc3988e9f08p-9));
          ;
          auto den =
          eve::reverse_horner(zz1, T(0x1.56709b0b644bep+8), T(-0x1.7fe08959063eep+8), T(0x1.26219af6a7f42p+7), T(-0x1.5f2a2b6bf5d8cp+4), T(0x1.0p0));
          ;
          auto vp  = num / den;
          zz1      = sqrt(zz1 + zz1);
          auto z   = pio_4(eve::as<T>()) - zz1;
          zz1      = fms(zz1, vp, T(0x1.1a62633145c07p-54)); // pio_2lo
          z        = z - zz1;
          zz1      = z + pio_4(eve::as<T>());
          return zz1;
        };
        auto case_2 = [](const T& x) { // x >=  0.625
          T    zz2 = sqr(x);
          auto num = zz2 * eve::reverse_horner(zz2, T(-0x1.0656c06ceafd5p+3), T(0x1.39007da779259p+4), T(-0x1.04331de27907bp+4)
                                              , T(0x1.5c74b178a2dd9p+2), T(-0x1.34341333e5c16p-1), T(0x1.16b9b0bd48ad3p-8));
          ;
          auto den =
          eve::reverse_horner(zz2, T(-0x1.898220a3607acp+5), T(0x1.1705684ffbf9dp+7), T(-0x1.265bb6d3576d7p+7)
                             , T(0x1.19fc025fe9054p+6), T(-0x1.d7b590b5e0eabp+3), T(0x1.0p0));
          ;
          auto z   = num / den;
          zz2      = fma(x, z, x);
          return zz2;
        };
        auto ct1    = T(0x1.4000000000000p-1); // 0.625;
        auto xgtct1 = x > ct1;
        auto res    = branch<scalar_value<T>>(xgtct1, case_1, case_2)(x);
        if constexpr( simd_value<T> ) { res = if_else(small, x, res); }
        return bit_xor(res, sgn);
      }
    }
    else return apply_over(eve::asin, a0);
  }

// -----------------------------------------------------------------------------------------------
// Masked cases
  template<conditional_expr C, value U>
  EVE_FORCEINLINE auto
  asin_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::asin, t);
  }

  template<conditional_expr C, decorator D, value U>
  EVE_FORCEINLINE auto
  asin_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
  {
    return mask_op(cond, d(eve::asin), t);
  }
}
