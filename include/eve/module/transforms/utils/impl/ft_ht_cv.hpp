//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/detail/combined_ops.hpp>
#include <type_traits>

namespace eve::detail
{

  template <int sign = 1, range  R>
  EVE_FORCEINLINE void ht_ft_cv_(EVE_SUPPORTS(cpu_)
                                , R& fr
                                , R& fi
                                , std::integral_constant<int, sign> const &)
  {
    std::cout << "icitte" << std::endl;
    auto n = std::size(fr);
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(fr[0])>;

    auto scramble = [](auto & fri, auto & frj, auto & fii, auto & fij){
      using t_t = std::remove_reference_t<decltype(fri)>;
      t_t q, r, s, t;
      if constexpr(sign > 0)
      {
        sd(fri, frj, q, r);
        sd(fii, fij, s, t);
      }
      else
      {
        sd(frj, fri, q, r);
        sd(fij, fii, s, t);
      }
      hsd(q, t, frj, fri);
      hsd(s, r, fii, fij);
    };
    constexpr i_t cardinal = expected_cardinal_v<e_t>;
    auto nfp = min(cardinal, n);
    for (i_t i=1, j=n-1; (i < j) && (i<nfp);  ++i, --j)
    {
      scramble(fr[i], fr[j], fi[i], fi[j]);
    }
    if (n > 2*cardinal)
    {

      auto ff = fr.data();
      auto gg = fi.data();

      auto fi = eve::algo::as_range(ff+cardinal,ff+n/2);
      auto fj = eve::views::reverse(eve::algo::as_range(ff+n/2+1, ff+n-cardinal+1));
      auto gi = eve::algo::as_range(gg+cardinal,gg+n/2);
      auto gj = eve::views::reverse(eve::algo::as_range(gg+n/2+1, gg+n-cardinal+1));

      auto view = eve::views::zip(fi, fj, gi, gj);
      auto doit = [scramble](auto zz, auto ignore){
        auto [fi_it, fj_it, gi_it, gj_it]= zz;
        auto [fi, fj, gi, gj] = eve::load[ignore](zz);
        scramble(fi, fj, gi, gj);
        eve::store[ignore](fi, fi_it);
        eve::store[ignore](fj, fj_it);
        eve::store[ignore](gi, gi_it);
        eve::store[ignore](gj, gj_it);
      };
      eve::algo::for_each[eve::algo::unroll<2>][eve::algo::no_aligning](view, doit);
   };
  }

  template <range  R>
  EVE_FORCEINLINE void ht_ft_cv_(EVE_SUPPORTS(cpu_)
                                , R& fr
                                , R& fi)
  {
    ht_ft_cv(fr, fi, std::integral_constant<int, 1>());
  }

    template <range  R>
  EVE_FORCEINLINE void inv_ht_ft_cv_(EVE_SUPPORTS(cpu_)
                                    , R& fr
                                    , R& fi)
  {
    ht_ft_cv(fr, fi, std::integral_constant<int, -1>());
  }
}
