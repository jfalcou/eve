//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/traits.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <typename RorI>
  struct types_to_consider_for
  {
    using type = kumi::tuple<value_type_t<RorI>>;
  };

  template <typename RorI>
  requires requires(RorI) { typename RorI::types_to_consider; }
  struct types_to_consider_for<RorI>
  {
    using type = typename RorI::types_to_consider;
  };

  template <typename RorI>
  using types_to_consider_for_t = typename types_to_consider_for<RorI>::type;
}
