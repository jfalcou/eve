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
#include <eve/module/fft/utils.hpp>

namespace eve::detail
{
  ///////////////////////////////////////////////////////////////////
  // fft depth first decimation in frequency
  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  fft_df_dif2_(EVE_SUPPORTS(cpu_), aos_type const &, R & f, T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  std::size(f);
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const i_t m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = rec( T(mh) );
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;
          auto pi0 = f.data()+i0;
          auto pi1 = f.data()+i1;
          auto u = *pi0;
          auto v = *pi1;
          *pi0 = (u + v);
          *pi1 = (u - v) *  exp_ipi( phi*j );
        }
      }
    }
    aos(revbin_permute)(f);
    aos(scaleit)(f, fac);
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  fft_df_dif2_(EVE_SUPPORTS(cpu_), soa_type const &, R & f, T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    constexpr size_t cardinal = eve::expected_cardinal_v<T>;
    using  c_t = complex<T>;
    auto n =  std::size(f);
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    std::vector<c_t> c(n);
    auto ldn = eve::countr_zero(n);
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const i_t m = (1UL<<ldm);
      const i_t mh = m >> 1;
      const T  phi = rec(T(mh));
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
            f.set(i1, (u - v)*exp_ipi( phi*j));
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
            eve::algo::for_each[eve::algo::expensive_callable][eve::algo::allow_frequency_scaling](
              view, [phi](auto zz, auto ignore) {
                auto [u_it, v_it, _] = zz;
                auto [u, v, idx] = eve::load[ignore](zz, eve::fixed<cardinal>{});

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
    soa(revbin_permute)(f);
    soa(scaleit)(f, fac);
   }
}
