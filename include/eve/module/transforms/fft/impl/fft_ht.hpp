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
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/utils.hpp>
#include <eve/module/transforms/fht.hpp>
#include <eve/module/transforms/permute/revbin_permute.hpp>
#include <type_traits>

namespace eve::detail
{

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE void
  fft_ht_(EVE_SUPPORTS(cpu_), aos_type const &, R & fr,  R & fi, T fac) noexcept
  {
    aos(ht_ft_cv)(fi, fr);
    aos(large_df_fht)(fr, T(1));
    aos(large_df_fht)(fi, T(1)) ;
    scaleit(fr, fi, fac*sqrt_2(as(fac)));
  }
}
