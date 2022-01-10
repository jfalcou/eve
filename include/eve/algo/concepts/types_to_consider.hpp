//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

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
