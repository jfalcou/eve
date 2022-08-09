//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/product_type.hpp>

namespace udt
{

struct point2D : eve::struct_support<point2D, std::int32_t, std::int32_t> {
  friend decltype(auto) get_x(eve::like<point2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_y(eve::like<point2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

struct line2D: eve::struct_support<line2D, point2D, point2D>
{
  friend decltype(auto) get_start(eve::like<line2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_end  (eve::like<line2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

}
