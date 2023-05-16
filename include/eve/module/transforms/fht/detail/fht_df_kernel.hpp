//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/utils.hpp>
#include <type_traits>

namespace eve::detail
{
  EVE_FORCEINLINE constexpr void
  df_2(auto f) noexcept // 2 elements
  {
     sd(f[0], f[1]);
  }

  EVE_FORCEINLINE constexpr void
  df_4(auto f) noexcept // 4 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t f0, f1, f2, f3;
    sd(f[0], f[2], f0, f1);
    sd(f[1], f[3], f2, f3);
    sd(f0, f2, f[0], f[1]);
    sd(f1, f3, f[2], f[3]);
  }

  EVE_FORCEINLINE constexpr void
  df_4_ind(auto f, auto k0, auto k1, auto k2, auto k3) noexcept // 4 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t f0, f1, f2, f3;
    sd(f[0], f[k1], f0, f1);
    sd(f[k2], f[k3], f2, f3);
    sd(f0, f2, f[0], f[k2]);
    sd(f1, f3, f[k1], f[k3]);
  }

  EVE_FORCEINLINE constexpr void
  df_8(auto f) noexcept // 8 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t g0, f0, f1, g1;
    sd(f[0], f[4], f0, g0);
    sd(f[2], f[6], f1, g1);
    sd(f0, f1);
    sd(g0, g1);
    e_t s1, c1, s2, c2;
    sd(f[1], f[5], s1, c1);
    sd(f[3], f[7], s2, c2);
    sd(s1, s2);
    sd(f0, s1, f[0], f[1]);
    sd(f1, s2, f[2], f[3]);
    c1 *=  sqrt_2(as<e_t>());
    c2 *=  sqrt_2(as<e_t>());
    sd(g0, c1, f[4], f[5]);
    sd(g1, c2, f[6], f[7]);
  }

  EVE_FORCEINLINE constexpr void
  df_16(auto f) noexcept // 8 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    using c_t =  complex<e_t>;
    const auto  invsqrt2 = invsqrt_2(as<e_t>());
    const auto  sqrt2    = sqrt_2(as<e_t>());
    e_t f0, f1, f2, f3;
    sd(f[0], f[8], f0, f1);
    sd(f[4], f[12], f2, f3);
    sd(f0, f2, f[0], f[4]);
    sd(f1, f3, f[8], f[12]);

    sd(f[2], f[10], f0, f1);
    sd(f[6], f[14], f2, f3);
    sd(f0, f2, f[2], f[6]);
    sd(f1, f3, f[10], f[14]);

    sd(f[1], f[9], f0, f1);
    sd(f[5], f[13], f2, f3);
    sd(f0, f2, f[1], f[5]);
    sd(f1, f3, f[9], f[13]);

    sd(f[3], f[11], f0, f1);
    sd(f[7], f[15], f2, f3);
    sd(f0, f2, f[3], f[7]);
    sd(f1, f3, f[11], f[15]);

    sd(f[0], f[2], f0, f1);
    sd(f[1], f[3], f2, f3);
    sd(f0, f2, f[0], f[1]);
    sd(f1, f3, f[2], f[3]);

    sd(f[4], f[6], f0, f1);
    f3 = sqrt2 * f[7];
    f2 = sqrt2 * f[5];
    sd(f0, f2, f[4], f[5]);
    sd(f1, f3, f[6], f[7]);

    e_t a, b, g0, g1, g2, g3;
    sd(f[10], f[14], a, b);
    a *= invsqrt2;
    b *= invsqrt2;
    sd(f[8], a, f0, f1);
    sd(f[12], b, g0, g1);
    sd(f[11], f[15], a, b);
    a *= invsqrt2;
    b *= invsqrt2;
    sd(f[9], a, f2, f3);
    sd(f[13], b, g2, g3);
    const e_t c1 = cos_pio_8(as<e_t>());
    const e_t s1 = sin_pio_8(as<e_t>());
    kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
    sd(f0, a, f[8], f[9]);
    sd(g1, b, f[14], f[15]);
    kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
    sd(g0, a, f[12], f[13]);
    sd(f1, b, f[10], f[11]);
  }

  template < bool final_radix_16 = true >
  EVE_FORCEINLINE constexpr void
  fht_df_kernel(auto f, auto log2_n, const bool simd = true) noexcept
  {
  //  requires(std::is_floating_point_v<typename R::value_type>)
    auto n = 1UL << log2_n;
    using i_t = decltype(n);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
//    using c_t =  complex<e_t>;
    [[maybe_unused]] const auto  invsqrt2 = invsqrt_2(as<e_t>());
    [[maybe_unused]] const auto  sqrt2    = sqrt_2(as<e_t>());
    if(log2_n == 1) { df_2(f); return; }
    if(log2_n == 2) { df_4(f); return; }
    auto o = one(as(n));
    const auto fn = f + n;
    i_t ldk = log2_n - 2;
    i_t thresh = final_radix_16 ? 2 : 1;
    for (  ; ldk>thresh;  ldk-=2)
    {
      i_t k   = o<<ldk;
      i_t kh  = k >> 1;
      i_t k2  = k << 1;
      i_t k3  = k2 + k;
      i_t k4  = k2 << 1;
//       std::cout << " n  " << n   << " ldk " << ldk << " k  " << k << std::endl;
//       std::cout << " k2 " << k2  << " k3  " << k3  << " k4 " << k4 << std::endl;
      const auto sqrt2 = eve::sqrt_2(as<e_t>());
      i_t cardinal = expected_cardinal_v<e_t>;
      for (auto fi=f, gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
      {
        e_t f0, f1, f2, f3;
        sd(fi[0], fi[k], f0, f1);
        sd(fi[k2], fi[k3], f2, f3);
        sd(f0, f2, fi[0], fi[k2]);
        sd(f1, f3, fi[k], fi[k3]);

        sd(gi[0], gi[k2], f0, f1);
        sd(gi[k], gi[k3], f2, f3);
        sd(f0, f2, gi[0], gi[k]);
        gi[k2] = sqrt2 * f1;
        gi[k3] = sqrt2 * f3;
      }

      auto tt = rec(4*e_t(kh));

      auto scramble = [](auto &dgik0, auto &dgik1, auto &dgik2, auto &dgik3,
                         auto &dfik0, auto &dfik1, auto &dfik2, auto &dfik3,
                         auto sc1b, auto cs1b, auto sc2b){
        using we_t = std::remove_reference_t<decltype(dgik0)>;
        using c_t =  decltype(cs1b);
        we_t a, b, g0, f0, f1, g1;
        sd(dgik0, dgik2, g0, a);
        sd(dfik1, dfik3, f1, b);
        auto [g2, f3] = cs1b*c_t(b, a);
        sd(dfik0, dfik2, f0, a);
        sd(dgik1, dgik3, g1, b);
        auto [f2, g3] = sc1b*c_t(b, a);
        sd(f2, f3, dfik2, a);
        sd(g2, g3, dgik2, b);
        kumi::tie(dfik3, dgik3) = kumi::to_tuple(sc2b*c_t(b, a));
        sd(f0, f1, dfik0, a);
        sd(g0, g1, dgik0, b);
        kumi::tie(dfik1, dgik1) = kumi::to_tuple(sc2b*c_t(b, a));
      };

      auto scalar = [&](auto i)
      {
        auto cs1 = exp_ipi(tt*i);
        auto [c1, s1] = cs1;
        auto cs2 =  sqr(cs1);
        auto [c2, s2] = cs2;
        using c_t =  complex<e_t>;
        auto cs1b = c_t(c1, -s1);
        auto sc1b = c_t(s1, -c1);
        auto sc2b = c_t(s2, -c2);
        for (auto fi=f+i, gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
        {
          scramble(gi[0], gi[k], gi[k2], gi[k3],
                   fi[0], fi[k], fi[k2], fi[k3],
                   sc1b, cs1b, sc2b);
        }
      };
      auto sm = min(cardinal, kh);
      for (i_t i=1; i < sm; i++) scalar(i);
      if (simd && (kh > cardinal))
      {
        auto phi0 = tt*cardinal;
        auto is = eve::views::iota(e_t(cardinal), kh-cardinal);
        auto phs= eve::views::iota_with_step(e_t{phi0}, tt, kh-cardinal);
        auto view = eve::views::zip(is, phs);
        auto doit = [scramble, k, k2, k3, k4, tt, &f, cardinal, fn](auto zz, auto ignore){
          auto [i, ph] = load[ignore](zz);
          auto cs1 = exp_ipi(tt*i);
          auto [c1, s1] = cs1;
          auto cs2 =  sqr(cs1);
          auto [c2, s2] = cs2;
          using c_t = decltype(cs1);
          auto cs1b = c_t(c1, -s1);
          auto sc1b = c_t(s1, -c1);
          auto sc2b = c_t(s2, -c2);
          auto i0 = size_t(i.get(0));
          for (auto fi=f+i0, gi=f+k-i0-cardinal+1;  fi<fn;  fi+=k4, gi+=k4)
          {
            auto dgik0  =reverse(load(gi+0 ));
            auto dgik1  =reverse(load(gi+k ));
            auto dgik2  =reverse(load(gi+k2));
            auto dgik3  =reverse(load(gi+k3));
            auto dfik0  =load(fi+0 );
            auto dfik1  =load(fi+k );
            auto dfik2  =load(fi+k2);
            auto dfik3  =load(fi+k3);
            scramble(dgik0, dgik1, dgik2, dgik3,
                     dfik0, dfik1, dfik2, dfik3,
                     sc1b, cs1b, sc2b);
            store(reverse(dgik0), gi+0 );
            store(reverse(dgik1), gi+k );
            store(reverse(dgik2), gi+k2);
            store(reverse(dgik3), gi+k3);
            store(dfik0, fi+0 );
            store(dfik1, fi+k );
            store(dfik2, fi+k2);
            store(dfik3, fi+k3);

          }
        };
        eve::algo::for_each[eve::algo::allow_frequency_scaling](view, doit);
      }
      else
      {
        for (i_t i=sm; i<kh; i++) scalar(i);
      }
    }

    if (is_odd(ldk))
    {
      for (e_t *fi=f; fi<fn; fi+=8)  df_8(fi);
    }
    else
    {
      if constexpr(final_radix_16)
      {
        for (auto fi=f; fi<fn; fi+=16) df_16(fi);
      }
      else
      {
        for (auto fi=f; fi<fn; fi+=4) df_4(fi);
      }
    }
  }
}
