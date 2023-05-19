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
#include <eve/module/transforms/fht/detail/fht_dt_steps.hpp>

namespace eve::detail
{
  template < bool initial_radix_16 = true >
  EVE_FORCEINLINE constexpr void
  fht_dt_kernel(auto f, auto log2_n, const bool simd = true) noexcept
  //  requires(std::is_floating_point_v<typename R::value_type>)
  {
    auto n = 1UL << log2_n;
    using i_t = decltype(n);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    using c_t =  complex<e_t>;
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
      sd(dgik0, dgik1, f0, f1);
      f3 = sqrt2 * dgik3;
      f2 = sqrt2 * dgik2;
      sd(f0, f2, dgik0, dgik2);
      sd(f1, f3, dgik1, dgik3);
    };

    if(log2_n == 1) { dt_2(f); return; }
    if(log2_n == 2) { dt_4(f); return; }
    const auto fn = f + n;
    i_t ldk;

    if ( is_even(log2_n) )    // n is a power of 4
    {
      if constexpr(initial_radix_16)
      {
        for (auto fi=f; fi<fn; fi+=16) dt_16(fi);
        ldk = 4;
      }
      else
      {
        for (auto fi=f; fi<fn; fi+=4) dt_4(fi);
        ldk = 2;
      }
    }
    else                              //  n is not a  power of 4
    {
      for (auto fi=f; fi<fn; fi+=8) dt_8(fi);
      ldk = 3;
    }
    for (  ; ldk<log2_n;  ldk+=2)
    {
      constexpr i_t k0 = 0;
      i_t k1   = 1 <<ldk;
      i_t kh  = k1 >> 1;
      i_t k2  = k1 << 1;
      i_t k3  = k2 + k1;
      i_t k4  = k2 << 1;

      for (auto fi=f, gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
      {
        scramble0(gi[k0], gi[k1], gi[k2], gi[k3]
                 , fi[k0], fi[k1], fi[k2], fi[k3]);
      }

      e_t tt = rec(e_t(kh*4));
      auto scalar = [&](auto i)
      {
        auto [c1, s1] = exp_ipi(tt*i);
        auto [c2, s2] = sqr(c_t(c1, s1));
        for (e_t *fi=f+i, *gi=f+k1-i;  fi<fn;  fi+=k4, gi+=k4)
        {
          e_t a, b, g0, f0, f1, g1, f2, g2, f3, g3;
          kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k1], gi[k1]);
          sd(fi[k0], a, f0, f1);
          sd(gi[k0], b, g0, g1);

          kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k3], gi[k3]);
          sd(fi[k2], a, f2, f3);
          sd(gi[k2], b, g2, g3);

          kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
          sd(f0, a, fi[0], fi[k2]);
          sd(g1, b, gi[k1], gi[k3]);

          kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
          sd(g0, a, gi[k0], gi[k2]);
          sd(f1, b, fi[k1], fi[k3]);
        }
      };
      i_t cardinal = eve::expected_cardinal_v<e_t>;
      auto sm = min(cardinal, kh);
      for (i_t i=1; i < sm; i++) scalar(i);
      if (simd && (kh > cardinal))
      {
        auto phi0 = tt*cardinal;
        auto is = eve::views::iota(e_t(cardinal), kh-cardinal);
        auto phs= eve::views::iota_with_step(e_t{phi0}, tt, kh-cardinal);
        auto view = eve::views::zip(is, phs);
        auto doit = [k1, k2, k3, k4, tt, f, cardinal, fn](auto zz, auto ignore){
          auto [i, ph] = load[ignore](zz);
          auto cs1 = exp_ipi(tt*i);
          auto [c1, s1] = cs1;
          using c_t =  decltype(cs1);
          auto [c2, s2] =  sqr(cs1);

          auto i0 = size_t(i.get(0));
          for (auto fi=f+i0, gi=f+k1-i0-cardinal+1;  fi<fn;  fi+=k4, gi+=k4)
          {
            auto dgik0 =reverse(load(gi+k0 ));
            auto dgik1 =reverse(load(gi+k1 ));
            auto dgik2 =reverse(load(gi+k2));
            auto dgik3 =reverse(load(gi+k3));
            auto dfik0 =load(fi+k0 );
            auto dfik1 =load(fi+k1 );
            auto dfik2 =load(fi+k2);
            auto dfik3 =load(fi+k3);
            using we_t = wide<e_t>;
            we_t a, b, g0, f0, f1, g1, f2, g2, f3, g3;
            kumi::tie(b, a) = kumi::to_tuple(c_t(s2, c2)*c_t(dfik1, dgik1));
            sd(dfik0, a, f0, f1);
            sd(dgik0, b, g0, g1);
            kumi::tie(b, a) = kumi::to_tuple(c_t(s2, c2)*c_t(dfik3, dgik3));
            sd(dfik2, a, f2, f3);
            sd(dgik2, b, g2, g3);
            kumi::tie(b, a) = kumi::to_tuple(c_t(s1, c1)*c_t(f2, g3));
            sd(f0, a, dfik0, dfik2);
            sd(g1, b, dgik1, dgik3);
            kumi::tie(b, a) = kumi::to_tuple(c_t(c1, s1)*c_t(g2, f3));
            sd(g0, a, dgik0, dgik2);
            sd(f1, b, dfik1, dfik3);
            store(reverse(dgik0) , gi+k0 );
            store(reverse(dgik1) , gi+k1 );
            store(reverse(dgik2), gi+k2);
            store(reverse(dgik3), gi+k3);
            store(dfik0 , fi+k0 );
            store(dfik1 , fi+k1 );
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
  }
}
