//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/product_type.hpp>

namespace udt
{

struct point2D : eve::product_type_base<point2D, std::int32_t, std::int32_t> {
  friend decltype(auto) get_x(eve::same_value_type<point2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_y(eve::same_value_type<point2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

struct line2D: eve::product_type_base<line2D, point2D, point2D>
{
  friend decltype(auto) get_start(eve::same_value_type<line2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_end  (eve::same_value_type<line2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

}
