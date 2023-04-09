//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <type_traits>
#include <vector>

namespace eve::detail
{
  template<typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , F const & fft
                            , R & f
                            , T const & fac) noexcept
  {
    auto conjmuli = [fac]<typename C>(C x){
     auto  [r, i] = x; return C(i, r)*fac;
    };
    eve::algo::transform_inplace(f, conjmuli);
    fft(f, fac);
  }
}
