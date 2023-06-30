//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex.hpp>

namespace eve
{
  template < int N > struct axis:std::integral_constant<int, N>{};
  auto _X(axis<1>{});
  auto _Y(axis<2>{});
  auto _Z(axis<3>{});
}
