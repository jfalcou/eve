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
  inline constexpr auto _X(axes<1>{});
  inline constexpr auto _Y(axes<2>{});
  inline constexpr auto _Z(axes<3>{});

  template < bool e > struct ext:std::integral_constant<bool, e>{};
  auto Extrinsic(ext<true>{});
  auto Intrinsic(ext<false>{});

  template < bool e > struct nor:std::integral_constant<bool, e>{};
  inline constexpr auto Assume_normalized(nor<false>{});
  inline constexpr auto Normalize(nor<true>{});
}
