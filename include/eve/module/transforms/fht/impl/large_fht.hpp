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

  template <range  R, floating_scalar_value T>
  EVE_FORCEINLINE void large_fht_(EVE_SUPPORTS(cpu_)
                               , aos_type const &
                               , R& fr
                               , T fac
                               , bool simd = true)
  {
    auto n =  std::size(fr);
    auto log2_n = eve::countr_zero(n); //eve::log2(n));
    fht_loc_df_core(fr.data(), log2_n, simd);
    aos(revbin_permute)(fr);
    aos(scaleit)(fr, fac*invsqrt_2(as(fac)));
  }
}
