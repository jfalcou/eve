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
#include <eve/module/fft/utils/aos_soa.hpp>
#include <type_traits>

namespace eve::detail
{
  template< range R>
  auto caos2csoa_(EVE_SUPPORTS(cpu_)
                 , R const & f) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    using c_t = typename R::value_type;
    eve::algo::soa_vector<c_t> r(size(f));
    for( auto e : f) r.set(i, e);
 //    auto n = size(f);
//     auto b = f.begin().base;
//     auto [bfr, bfi] = b;
//     auto fr = eve::algo::as_range(bfr, bfr+n);
//     auto fi = eve::algo::as_range(bfi, bfi+n);
//     return kumi::make_tuple(fr, fi);
  }
}
