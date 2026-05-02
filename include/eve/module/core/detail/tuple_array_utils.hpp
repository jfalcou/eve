//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::_
{

  // return a tuple containing the elements of the input tuple
  // converted to their upgradedcommon value type
  template <eve::product_type PT> constexpr
  auto upgrade_tuple(PT t){
    if constexpr(PT::size() == 0)
      return t;
    else
    {
      using r_t = kumi::apply_traits_t<eve::common_value, PT>;
      return kumi::map([](auto m){return upgrade(r_t(m)); }, t);
    }
  };
}
