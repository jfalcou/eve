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

using i32_x2    = kumi::tuple<std::int32_t, std::int32_t>;

struct point2D : i32_x2 {
  friend decltype(auto) get_x(eve::same_value_type<point2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_y(eve::same_value_type<point2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

using points2D_2 = kumi::tuple<point2D, point2D>;

struct line2D: points2D_2
{
  friend decltype(auto) get_start(eve::same_value_type<line2D> auto&& self) { return get<0>(std::forward<decltype(self)>(self)); }
  friend decltype(auto) get_end  (eve::same_value_type<line2D> auto&& self) { return get<1>(std::forward<decltype(self)>(self)); }
};

}

template<>              struct eve::is_product_type<udt::point2D> : std::true_type {};
template<>              struct std::tuple_size<udt::point2D>      : std::tuple_size<udt::i32_x2> {};
template<std::size_t I> struct std::tuple_element<I,udt::point2D> : std::tuple_element<I, udt::i32_x2> {};

template<>              struct eve::is_product_type<udt::line2D> : std::true_type {};
template<>              struct std::tuple_size<udt::line2D>      : std::tuple_size<udt::points2D_2> {};
template<std::size_t I> struct std::tuple_element<I,udt::line2D> : std::tuple_element<I, udt::points2D_2> {};
