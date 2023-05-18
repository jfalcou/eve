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
//#include <omp.h>

namespace eve::detail
{

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE void
  fft_ht_(EVE_SUPPORTS(cpu_), R & fr,  R & fi, T fac) noexcept
  {
    ht_ft_cv(fi, fr);
//     omp_set_num_threads(2);
//     #pragma omp parallel for
//     for(int i = 0; i <= 1; ++i)
//     {
//       if (i == 0)
//       {
//         large_df_fht(fr, T(1));
//         scaleit(fr, fac*sqrt_2(as(fac)));
//       }
//       if (i == 1)
//       {
//         large_df_fht(fi, T(1));
//         scaleit(fi, fac*sqrt_2(as(fac)));
//       }
//     }
    large_df_fht(fr, T(1));
    large_df_fht(fi, T(1)) ;
    scaleit(fr, fi, fac*sqrt_2(as(fac)));
  }
}
