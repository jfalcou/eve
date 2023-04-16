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
  template<range R>
  EVE_FORCEINLINE auto soac2ri_(EVE_SUPPORTS(cpu_)
                               , R & f ) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n = size(f);
    auto b = f.begin().base;
    auto [bfr, bfi] = b;
    auto fr = eve::algo::as_range(bfr, bfr+n);
    auto fi = eve::algo::as_range(bfi, bfi+n);
    return kumi::make_tuple(fr, fi);
  }
}
