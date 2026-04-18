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
  // return an array containing the elements of the input tuple
  // converted to their common value type
  template <eve::product_type PT> constexpr
  auto to_array(PT t) noexcept
  {
    using r_t = kumi::apply_traits_t<eve::common_value, PT>;
    using a_t = std::array<r_t, PT::size()>;
    return std::bit_cast<a_t>(t);
  };

  // return a tuple containing the elements of the input tuple
  // converted to their upgradedcommon value type
  template <eve::product_type PT> constexpr
  auto upg(PT t){
    if constexpr(PT::size() == 0)
      return t;
    else
    {
      using r_t = kumi::apply_traits_t<eve::common_value, PT>;
      return kumi::map([](auto m){return upgrade(r_t(m)); }, t);
    }
  };

  // return a tuple containing the elements of the input array
  template <eve::value T, auto N> auto to_tuple(std::array<T, N> a)
  {
    using f_t = kumi::result::fill_t<N, T>;
    return std::bit_cast<f_t>(a);
  };
}
