//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(ht_ft_cv_, ht_ft_cv);
  EVE_MAKE_CALLABLE(inv_ht_ft_cv_, inv_ht_ft_cv);
}

#include <eve/module/transforms/utils/impl/ft_ht_cv.hpp>
