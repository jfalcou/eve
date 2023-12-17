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
struct plain_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using plain_type = decorated<plain_()>;
inline constexpr plain_type const plain = {};
}
