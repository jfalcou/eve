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
struct musl_t
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using musl_type = decorated<musl_t()>;
inline constexpr musl_type const musl_ = {};
}
