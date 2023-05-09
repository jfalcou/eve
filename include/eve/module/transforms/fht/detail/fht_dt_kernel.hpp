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
    if ( log2_n<=2 )
    {
        if ( log2_n==1 )  // two point fht
        {
            sd(f[0], f[1]);
        }
        else if ( log2_n==2 )  // four point fht
        {
            e_t f0, f1, f2, f3;
            sd(f[0], f[1], f0, f1);
            sd(f[2], f[3], f2, f3);
            sd(f0, f2, f[0], f[2]);
            sd(f1, f3, f[1], f[3]);
        }
        return;
    }

    auto fn = f + n;
    i_t ldk = log2_n & 1;

    if ( ldk==0 )    // log2_n is multiple of 2  => n is a power of 4
    {
      if constexpr(initial_radix_16)
      {
        for (auto fi=f; fi<fn; fi+=16)  // radix-16 step
        {
          e_t f0, f1, f2, f3;
          sd(fi[0], fi[1], f0, f1);
          sd(fi[2], fi[3], f2, f3);
          sd(f0, f2, fi[0], fi[2]);
          sd(f1, f3, fi[1], fi[3]);

          sd(fi[4], fi[5], f0, f1);
          sd(fi[6], fi[7], f2, f3);
          sd(f0, f2, fi[4], fi[6]);
          sd(f1, f3, fi[5], fi[7]);

          sd(fi[8], fi[9], f0, f1);
          sd(fi[10], fi[11], f2, f3);
          sd(f0, f2, fi[8], fi[10]);
          sd(f1, f3, fi[9], fi[11]);

          sd(fi[12], fi[13], f0, f1);
          sd(fi[14], fi[15], f2, f3);
          sd(f0, f2, fi[12], fi[14]);
          sd(f1, f3, fi[13], fi[15]);

          sd(fi[0], fi[4], f0, f1);
          sd(fi[8], fi[12], f2, f3);
          sd(f0, f2, fi[0], fi[8]);
          sd(f1, f3, fi[4], fi[12]);

          sd(fi[2], fi[6], f0, f1);
          f3 = sqrt2 * fi[14];
          f2 = sqrt2 * fi[10];
          sd(f0, f2, fi[2], fi[10]);
          sd(f1, f3, fi[6], fi[14]);

          e_t a, b, g0, g1, g2, g3;
          sd(fi[5], fi[7], a, b);
          a *= invsqrt2;
          b *= invsqrt2;
          sd(fi[1], a, f0, f1);
          sd(fi[3], b, g0, g1);
          sd(fi[13], fi[15], a, b);
          a *= invsqrt2;
          b *= invsqrt2;
          sd(fi[9], a, f2, f3);
          sd(fi[11], b, g2, g3);
          e_t c1 = e_t( 0.923879532511286756128183189397);
          e_t s1 =  e_t( 0.382683432365089771728459984029);
          kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
          sd(f0, a, fi[1], fi[9]);
          sd(g1, b, fi[7], fi[15]);
          kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
          sd(g0, a, fi[3], fi[11]);
          sd(f1, b, fi[5], fi[13]);
        }
        ldk = 4;
      }
      else
      {
        for (auto fi=f; fi<fn; fi+=4)  // radix-4 step
        {
          e_t f0, f1, f2, f3;
          sd(fi[0], fi[1], f0, f1);
          sd(fi[2], fi[3], f2, f3);
          sd(f0, f2, fi[0], fi[2]);
          sd(f1, f3, fi[1], fi[3]);
        }
        ldk = 2;
      }
    }
    else          // ldk==1,  n is no power of 4
    {
      for (auto fi=f; fi<fn; fi+=8)  // radix-8 step
      {
        e_t g0, f0, f1, g1;
        sd(fi[0], fi[1], f0, g0);
        sd(fi[2], fi[3], f1, g1);

        sd(f0, f1);
        sd(g0, g1);

        e_t s1, c1, s2, c2;
        sd(fi[4], fi[5], s1, c1);
        sd(fi[6], fi[7], s2, c2);

        sd(s1, s2);

        sd(f0, s1, fi[0], fi[4]);
        sd(f1, s2, fi[2], fi[6]);

        c1 *= sqrt2;
        c2 *= sqrt2;

        sd(g0, c1, fi[1], fi[5]);
        sd(g1, c2, fi[3], fi[7]);
      }
      ldk = 3;
    }
    for (  ; ldk<log2_n;  ldk+=2)
    {
      i_t k   = 1 <<ldk;
      i_t kh  = k >> 1;
      i_t k2  = k << 1;
      i_t k3  = k2 + k;
      i_t k4  = k2 << 1;

      for (auto fi=f, gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
      {
        e_t f0, f1, f2, f3;
        sd(fi[0], fi[k], f0, f1);
        sd(fi[k2], fi[k3], f2, f3);
        sd(f0, f2, fi[0], fi[k2]);
        sd(f1, f3, fi[k], fi[k3]);

        sd(gi[0], gi[k], f0, f1);
        f3 = sqrt2 * gi[k3];
        f2 = sqrt2 * gi[k2];
        sd(f0, f2, gi[0], gi[k2]);
        sd(f1, f3, gi[k], gi[k3]);
      }

      e_t tt = rec(e_t(kh*4));
      auto scalar = [&](auto i)
      {
        auto [c1, s1] = exp_ipi(tt*i);
        auto [c2, s2] = sqr(c_t(c1, s1));
        for (e_t *fi=f+i, *gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
        {
          e_t a, b, g0, f0, f1, g1, f2, g2, f3, g3;
          kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k], gi[k]);
          sd(fi[0], a, f0, f1);
          sd(gi[0], b, g0, g1);

          kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k3], gi[k3]);
          sd(fi[k2], a, f2, f3);
          sd(gi[k2], b, g2, g3);

          kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
          sd(f0, a, fi[0], fi[k2]);
          sd(g1, b, gi[k], gi[k3]);

          kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
          sd(g0, a, gi[0], gi[k2]);
          sd(f1, b, fi[k], fi[k3]);
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
        auto doit = [k, k2, k3, k4, tt, f, cardinal, fn](auto zz, auto ignore){
          auto [i, ph] = load[ignore](zz);
          auto cs1 = exp_ipi(tt*i);
          auto [c1, s1] = cs1;
          using c_t =  decltype(cs1);
          auto [c2, s2] =  sqr(cs1);

          auto i0 = size_t(i.get(0));
          for (auto fi=f+i0, gi=f+k-i0-cardinal+1;  fi<fn;  fi+=k4, gi+=k4)
          {
            auto dgi0  =reverse(load(gi+0 ));
            auto dgik  =reverse(load(gi+k ));
            auto dgik2 =reverse(load(gi+k2));
            auto dgik3 =reverse(load(gi+k3));
            auto dfi0  =load(fi+0 );
            auto dfik  =load(fi+k );
            auto dfik2 =load(fi+k2);
            auto dfik3 =load(fi+k3);
            using we_t = wide<e_t>;
            we_t a, b, g0, f0, f1, g1, f2, g2, f3, g3;
            kumi::tie(b, a) = kumi::to_tuple(c_t(s2, c2)*c_t(dfik, dgik));
            sd(dfi0, a, f0, f1);
            sd(dgi0, b, g0, g1);
            kumi::tie(b, a) = kumi::to_tuple(c_t(s2, c2)*c_t(dfik3, dgik3));
            sd(dfik2, a, f2, f3);
            sd(dgik2, b, g2, g3);
            kumi::tie(b, a) = kumi::to_tuple(c_t(s1, c1)*c_t(f2, g3));
            sd(f0, a, dfi0, dfik2);
            sd(g1, b, dgik, dgik3);
            kumi::tie(b, a) = kumi::to_tuple(c_t(c1, s1)*c_t(g2, f3));
            sd(g0, a, dgi0, dgik2);
            sd(f1, b, dfik, dfik3);
            store(reverse(dgi0) , gi+0 );
            store(reverse(dgik) , gi+k );
            store(reverse(dgik2), gi+k2);
            store(reverse(dgik3), gi+k3);
            store(dfi0 , fi+0 );
            store(dfik , fi+k );
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
