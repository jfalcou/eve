//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  EVE_FORCEINLINE constexpr void
  dt_2(auto f) noexcept // 2 elements
  {
     sd(f[0], f[1]);
  }

  EVE_FORCEINLINE constexpr void
  dt_4(auto f) noexcept // 4 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t f0, f1, f2, f3;
    sd(f[0], f[2], f0, f1);
    sd(f[1], f[3], f2, f3);
    sd(f0, f2, f[0], f[1]);
    sd(f1, f3, f[2], f[3]);
  }

  EVE_FORCEINLINE constexpr void
  dt_4_ind(auto f, auto k0, auto k1, auto k2, auto k3) noexcept // 4 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t f0, f1, f2, f3;
    sd(f[k0], f[k2], f0, f1);
    sd(f[k1], f[k3], f2, f3);
    sd(f0, f2, f[k0], f[k1]);
    sd(f1, f3, f[k2], f[k3]);
  }

  EVE_FORCEINLINE constexpr void
  dt_8(auto f) noexcept // 8 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    const auto  sqrt2 = sqrt_2(as<e_t>());
    e_t g0, f0, f1, g1;
    sd(f[0], f[1], f0, g0);
    sd(f[2], f[3], f1, g1);
    sd(f0, f1);
    sd(g0, g1);
    e_t s1, c1, s2, c2;
    sd(f[4], f[5], s1, c1);
    sd(f[6], f[7], s2, c2);
    sd(s1, s2);
    sd(f0, s1, f[0], f[4]);
    sd(f1, s2, f[2], f[6]);
    c1 *= sqrt2;
    c2 *= sqrt2;
    sd(g0, c1, f[1], f[5]);
    sd(g1, c2, f[3], f[7]);
  }

  EVE_FORCEINLINE constexpr void
  dt_16(auto f) noexcept // 16 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    using c_t =  complex<e_t>;
    const auto  invsqrt2 = invsqrt_2(as<e_t>());
    const auto  sqrt2    = sqrt_2(as<e_t>());
    e_t f0, f1, f2, f3;
    sd(f[0], f[1], f0, f1);
    sd(f[2], f[3], f2, f3);
    sd(f0, f2, f[0], f[2]);
    sd(f1, f3, f[1], f[3]);
    
    sd(f[4], f[5], f0, f1);
    sd(f[6], f[7], f2, f3);
    sd(f0, f2, f[4], f[6]);
    sd(f1, f3, f[5], f[7]);
    
    sd(f[8], f[9], f0, f1);
    sd(f[10], f[11], f2, f3);
    sd(f0, f2, f[8], f[10]);
    sd(f1, f3, f[9], f[11]);
    
    sd(f[12], f[13], f0, f1);
    sd(f[14], f[15], f2, f3);
    sd(f0, f2, f[12], f[14]);
    sd(f1, f3, f[13], f[15]);
    
    sd(f[0], f[4], f0, f1);
    sd(f[8], f[12], f2, f3);
    sd(f0, f2, f[0], f[8]);
    sd(f1, f3, f[4], f[12]);
    
    sd(f[2], f[6], f0, f1);
    f3 = sqrt2 * f[14];
    f2 = sqrt2 * f[10];
    sd(f0, f2, f[2], f[10]);
    sd(f1, f3, f[6], f[14]);
    
    e_t a, b, g0, g1, g2, g3;
    sd(f[5], f[7], a, b);
    a *= invsqrt2;
    b *= invsqrt2;
    sd(f[1], a, f0, f1);
    sd(f[3], b, g0, g1);
    sd(f[13], f[15], a, b);
    a *= invsqrt2;
    b *= invsqrt2;
    sd(f[9], a, f2, f3);
    sd(f[11], b, g2, g3);
    const e_t c1 = cos_pio_8(as<e_t>());
    const e_t s1 = sin_pio_8(as<e_t>());
    kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
    sd(f0, a, f[1], f[9]);
    sd(g1, b, f[7], f[15]);
    kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
    sd(g0, a, f[3], f[11]);
    sd(f1, b, f[5], f[13]);
  }
}
