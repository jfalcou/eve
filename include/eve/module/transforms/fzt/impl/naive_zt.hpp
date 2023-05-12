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
#include <eve/module/transforms/utils.hpp>
#include <type_traits>

namespace eve::detail
{

  template<eve::algo::relaxed_range R, value T>
  EVE_FORCEINLINE constexpr void
  naive_zt_(EVE_SUPPORTS(cpu_), R & aa, T z) noexcept
  {
    using  t_t = decltype(read(aa.data()));
    auto N =  std::size(aa);
    using i_t = decltype(N);
    std::vector<t_t> c(N);

    auto a = aa.data();
    for (i_t w=0; w<N; ++w)
    {
      t_t r = zero(as<t_t>());
      t_t zw = one(as<t_t>()); //z^0 at start
      t_t step =  pow(z, w);   //z^w
      for (i_t k=0; k<N; ++k)
      {   r += (*(a+k)) *zw;
        zw *= step;
      }
      c[w] = r;
    }
    std::copy(c.begin(), c.end(), aa.begin());
  }
}
