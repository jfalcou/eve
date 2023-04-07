//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <vector>
#include <eve/module/fft/regular/revbin_permute.hpp>

namespace eve::detail
{

  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  fft_df2_(EVE_SUPPORTS(cpu_), std::vector<eve::complex<T>> & f, T1 fac, T1 s) noexcept
  {
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;
          auto u = f[i0];
          auto v = f[i1];

          f[i0] = (u + v);
          f[i1] = (u - v) *  exp_ipi( phi*j );
        }
      }
    }
    std::cout << "vector" << std::endl;
    f = revbin_permute(f);
    for(size_t i=0; i < n; ++i) f[i] *= fac;
    return f;
  }

  template<value T, value T1>
  constexpr auto fft_df2_scalar(EVE_SUPPORTS(cpu_)
                         , eve::algo::soa_vector<eve::complex<T>> & f
                         , T1 fac
                         , T1 s) noexcept
  {
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n);
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;
          auto u = f.get(i0);
          auto v = f.get(i1);

          f.set(i0, (u + v));
          f.set(i1, (u - v) *  exp_ipi( phi*j));
        }
      }
    }
    revbin_permute(f);

    for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
    return f;
  }


  template<value T, value T1>
  constexpr auto fft_df2_(EVE_SUPPORTS(cpu_)
                         , eve::algo::soa_vector<eve::complex<T>> & f
                         , T1 fac
                         , T1 s) noexcept
  {
    size_t cardinal = eve::nofs_cardinal_v<T>;
    using  c_t = complex<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n);
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const ulong m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = s / T(mh);
      if (cardinal >=  mh)
      {
        for (i_t r=0; r<n; r+=m)
        {
         for (i_t j=0; j<mh; ++j)
          {
            i_t i0 = r + j;
            i_t i1 = i0 + mh;
            auto u = f.get(i0);
            auto v = f.get(i1);
            f.set(i0, (u + v));
            f.set(i1, (u - v) *  exp_ipi( phi*j));
          }
        }
      }
      else
      {
        for (i_t r=0; r<n; r+=m)
        {
          auto doit = [phi](
            eve::algo::soa_vector<eve::complex<T>>& f,
            std::ptrdiff_t r,
            std::ptrdiff_t mh) {
            EVE_ASSERT(mh > eve::nofs_cardinal_v<T>, "");
            auto s = f.begin() + r;
            auto m = s + mh;

            // maybe uint64_t for doubles
            auto view = eve::views::zip(eve::algo::as_range(s, m), m,
                                        eve::views::iota(std::uint32_t{0}));

            // transform does
            eve::algo::for_each[eve::algo::expensive_callable](
              view, [phi](auto zz, auto ignore) {
                auto [u_it, v_it, _] = zz;
                auto [u, v, idx] = eve::load[ignore](zz);

                eve::store[ignore]((u + v), u_it);
                eve::store[ignore](
                  (u - v) * eve::exp_ipi(phi*eve::convert(idx, eve::as<T>{})),
                  v_it);
              });
          };
          doit(f, r, mh);
        }
      }
    }
    f = revbin_permute(f);
    for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
    return f;
  }
}
