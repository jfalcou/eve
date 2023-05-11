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
#include <eve/module/transforms/fht/detail/ht_shft.hpp>
#include <eve/module/transforms/fht/detail/fht_dt_kernel.hpp>
#include <type_traits>

namespace eve::detail
{


  template < bool is_final_radix_16 = true >
  constexpr void
  fht_loc_dt_core(auto f, auto log2_n, bool simd) noexcept
  // requires(std::is_floating_point_v<typename R::value_type>)
  {
    if ( log2_n <= 12 )  // sizeof(Type)*(2**threshold) <= L1_CACHE_BYTES
    {
      fht_dt_kernel<is_final_radix_16>(f, log2_n, simd);
      return;
    }
    else
    {
      using i_t = decltype(log2_n);
      for (i_t ldm=1; ldm<log2_n; ++ldm)
        fht_loc_dt_core(f+(1UL<<ldm), ldm, simd);

      for (i_t ldm=1; ldm<=log2_n; ++ldm)
      {
        const i_t m = (1UL<<ldm);
        const i_t mh = (m>>1);

        ht_shft_simd(f+mh, mh);

          auto f1 = eve::algo::as_range(f, f+mh);
          auto f2 = eve::algo::as_range(f+mh, f+2*mh);
          auto view = eve::views::zip(f1, f2);
          auto doit = [](auto zz, auto ignore){
            auto [f1_it, f2_it] = zz;
            auto [f1, f2] = eve::load[ignore](zz);
            sd(f1, f2);
            store[ignore](f1, f1_it);
            store[ignore](f2, f2_it);
          };
         eve::algo::for_each[eve::algo::unroll<2>](view, doit);
 //        for (i_t t1=0, t2=mh;  t1<mh;  ++t1, ++t2)
//           sd(f[t1], f[t2]);
      }
    }
  }

  template <range  R, floating_scalar_value T>
  EVE_FORCEINLINE void fht_dit_loc_(EVE_SUPPORTS(cpu_)
                               , aos_type const &
                               , R& fr
                               , T fac
                               , bool simd = true)
  {
    auto n =  std::size(fr);
    auto log2_n = eve::countr_zero(n); //eve::log2(n));
    revbin_permute(fr);
    fht_loc_dt_core(fr.data(), log2_n, simd);
    scaleit(fr, fac);
  }
}
