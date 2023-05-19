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
#include <eve/module/transforms/fht/detail/fht_df_steps.hpp>

namespace eve::detail
{

  template < bool final_radix_16 = true >
  EVE_FORCEINLINE constexpr void
  fht_df_kernel(auto f, auto log2_n, const bool simd = true) noexcept
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    using i_t =as_integer_t<e_t>;
    auto n = i_t(1) << log2_n;
    [[maybe_unused]] const auto  invsqrt2 = invsqrt_2(as<e_t>());
    [[maybe_unused]] const auto  sqrt2    = sqrt_2(as<e_t>());

    auto scramble0 = [sqrt2](auto &dgik0, auto &dgik1, auto &dgik2, auto &dgik3,
                             auto &dfik0, auto &dfik1, auto &dfik2, auto &dfik3){
      using t_t = std::remove_reference_t<decltype(dgik0)>;
      t_t f0, f1, f2, f3;
      sd(dfik0, dfik1, f0, f1);
      sd(dfik2, dfik3, f2, f3);
      sd(f0, f2, dfik0, dfik2);
      sd(f1, f3, dfik1, dfik3);
      sd(dgik0, dgik2, f0, f1);
      sd(dgik1, dgik3, f2, f3);
      sd(f0, f2, dgik0, dgik1);
      dgik2 = sqrt2 * f1;
      dgik3 = sqrt2 * f3;
    };

    if(log2_n == 1) { df_2(f); return; }
    if(log2_n == 2) { df_4(f); return; }
    auto o = one(as(n));
    const auto fn = f + n;
    i_t ldk = log2_n - 2;
    i_t thresh = final_radix_16 ? 2 : 1;
    for (  ; ldk>thresh;  ldk-=2)
    {
      constexpr i_t k0  = 0;
      i_t k1  = o<<ldk;
      i_t kh  = k1>> 1;
      i_t k2  = k1<< 1;
      i_t k3  = k2 + k1;
      i_t k4  = k2 << 1;

      using fix4 = fixed<4>;
      using we4_t = eve::wide<e_t, fix4>;
      i_t cardinal = eve::expected_cardinal_v<we4_t>;
      i_t shft = 4*k4*cardinal;

      if (n >= shft)
      {
        using wi4_t =  eve::as_integer_t<we4_t>;
        wi4_t ramp([](auto i,  auto){return i; });
        auto idx = ramp*k4;
        for (auto fi=f, gi=f+kh;  fi<fn;  fi+=shft, gi+=shft)
        {
          auto dfik0 = eve::gather(fi+k0, idx);
          auto dfik1 = eve::gather(fi+k1, idx);
          auto dfik2 = eve::gather(fi+k2, idx);
          auto dfik3 = eve::gather(fi+k3, idx);
          auto dgik0 = eve::gather(gi+k0, idx);
          auto dgik1 = eve::gather(gi+k1, idx);
          auto dgik2 = eve::gather(gi+k2, idx);
          auto dgik3 = eve::gather(gi+k3, idx);
          scramble0(dgik0, dgik1, dgik2, dgik3, dfik0, dfik1, dfik2, dfik3);
          scatter(gi+k0, idx, dgik0);
          scatter(gi+k1, idx, dgik1);
          scatter(gi+k2, idx, dgik2);
          scatter(gi+k3, idx, dgik3);
          scatter(fi+k0, idx, dfik0);
          scatter(fi+k1, idx, dfik1);
          scatter(fi+k2, idx, dfik2);
          scatter(fi+k3, idx, dfik3);
        }
      }
      else
      {
        for (auto fi=f, gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
          scramble0(gi[k0], gi[k1], gi[k2], gi[k3], fi[k0], fi[k1], fi[k2], fi[k3]);
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
        for (auto fi=f+i, gi=f+k1-i;  fi<fn;  fi+=k4, gi+=k4)
        {
          scramble(gi[k0], gi[k1], gi[k2], gi[k3],
                   fi[k0], fi[k1], fi[k2], fi[k3],
                   sc1b, cs1b, sc2b);
        }
      };
      i_t exp_card = expected_cardinal_v<e_t>;
      auto sm = min(exp_card, kh);
      for (i_t i=1; i < sm; i++) scalar(i);
      if (simd && (kh > exp_card))
      {
        auto phi0 = tt*exp_card;
        auto is = eve::views::iota(e_t(exp_card), kh-exp_card);
        auto phs= eve::views::iota_with_step(e_t{phi0}, tt, kh-exp_card);
        auto view = eve::views::zip(is, phs);
        auto doit = [scramble, k1, k2, k3, k4, tt, &f, exp_card, fn](auto zz, auto ignore){
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
          for (auto fi=f+i0, gi=f+k1-i0-exp_card+1;  fi<fn;  fi+=k4, gi+=k4)
          {
            auto dgik0  =reverse(load(gi+k0 ));
            auto dgik1  =reverse(load(gi+k1));
            auto dgik2  =reverse(load(gi+k2));
            auto dgik3  =reverse(load(gi+k3));
            auto dfik0  =load(fi+k0 );
            auto dfik1  =load(fi+k1);
            auto dfik2  =load(fi+k2);
            auto dfik3  =load(fi+k3);
            scramble(dgik0, dgik1, dgik2, dgik3,
                     dfik0, dfik1, dfik2, dfik3,
                     sc1b, cs1b, sc2b);
            store(reverse(dgik0), gi+k0 );
            store(reverse(dgik1), gi+k1);
            store(reverse(dgik2), gi+k2);
            store(reverse(dgik3), gi+k3);
            store(dfik0, fi+k0 );
            store(dfik1, fi+k1);
            store(dfik2, fi+k2);
            store(dfik3, fi+k3);

          }
        };
        eve::algo::for_each[eve::algo::allow_frequency_scaling](view, doit);
      }
      else for (i_t i=sm; i<kh; i++) scalar(i);
    }

    if (is_odd(ldk)) for (e_t *fi=f; fi<fn; fi+=8)  df_8(fi);
    else
    {
      if constexpr(final_radix_16)  for (auto fi=f; fi<fn; fi+=16) df_16(fi);
      else                          for (auto fi=f; fi<fn; fi+=4)  df_4(fi);
    }
  }
}
