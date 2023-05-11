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
#include <iostream>

namespace eve::detail
{
  template<typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , F const & fft
                            , R & f
                            , T const & fac) noexcept
  requires(eve::algo::is_soa_vector_v<R>)
  {
    auto conjmuli = []<typename C>(C x) noexcept {
      auto  [r, i] = x; return C(i, r);
    };
    eve::algo::transform_inplace(f, conjmuli);
    fft(f, fac);
    eve::algo::transform_inplace(f, conjmuli);
  }

  template<typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , F const & fft
                            , R & fr
                            , R & fi
                            , T const & fac) noexcept
  requires(std::is_floating_point_v<typename R::value_type>)
  {
    fft(fi, fr, fac);
  }


}
