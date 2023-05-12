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
      auto ffr = fr.data();
      auto ffi = fi.data();
      auto siz = n/2-cardinal;
      using idx_t = as_integer_t<e_t>;
      auto is = eve::views::iota(idx_t(nfp), siz);
      auto doit = [cardinal, ffr, ffi, n, scramble](auto zz, auto ignore){
        auto ii = eve::load[ignore](zz);
        auto j = n-ii.get(cardinal-1) ;
        auto i = ii.get(0);
        auto fri = load[ignore](ffr+i);
        auto frj = reverse(load[ignore](ffr+j));
        auto fii = load[ignore](ffi+i);
        auto fij = reverse(load[ignore](ffi+j));

        scramble(fri, frj, fii, fij);
        eve::store[ignore](fri, ffr+i);
        eve::store[ignore](reverse(frj), ffr+j);
        eve::store[ignore](fii, ffi+i);
        eve::store[ignore](reverse(fij), ffi+j);
      };
      eve::algo::for_each[eve::algo::unroll<2>](is, doit);
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
