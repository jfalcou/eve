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
  template < int N > struct axes:std::integral_constant<int, N>{};
  auto _X(axes<1>{});
  auto _Y(axes<2>{});
  auto _Z(axes<3>{});

  template < bool e > struct ext:std::integral_constant<bool, e>{};
  auto Extrinsic(ext<true>{});
  auto Intrinsic(ext<false>{});

  template < bool e > struct nor:std::integral_constant<bool, e>{};
  auto Assume_normalized(nor<false>{});
  auto Normalize(nor<true>{});
}
