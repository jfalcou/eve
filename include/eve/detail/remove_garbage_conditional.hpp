//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/conditional.hpp>
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
  //================================================================================================
  // Turn a conditional into a mask, ensure that all inactive lanes are set to false
  //================================================================================================
  template<conditional_expr C, typename Target>
  EVE_FORCEINLINE auto expand_mask_no_garbage(C const& c, as<Target> const&)
  {
    auto msk = c.mask(as<Target>{});
    if constexpr (!relative_conditional_expr<C>) msk = remove_garbage(msk);
    return as_logical_t<Target>(msk);
  }
}
