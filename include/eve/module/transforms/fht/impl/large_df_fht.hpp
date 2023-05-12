//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/transforms/utils.hpp>
#include <eve/module/transforms/fht/detail/fht_df_loc_kernel.hpp>
#include <type_traits>

namespace eve::detail
{

  template <eve::algo::relaxed_range  R, floating_scalar_value T>
  EVE_FORCEINLINE void large_df_fht_(EVE_SUPPORTS(cpu_)
                               , R& fr
                               , T fac
                               , bool simd = true)
  {
    auto n =  std::size(fr);
    auto l2_n = eve::countr_zero(n); //log2(n));
    fht_loc_df_core(fr.data(), l2_n, simd);
    revbin_permute(fr);
    scaleit(fr, fac*invsqrt_2(as(fac)));
  }
}
