//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/api/udt/udt.hpp"
#include <eve/wide.hpp>
#include <utility>

//==================================================================================================
// Operator==
//==================================================================================================
TTS_CASE("Check eve::wide<udt> operator==")
{
  udt::grid2d::reset();
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{i%2, i%5 ? -1 : 1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{i%3, i%3 ? -1 : 1}; };

  eve::logical<eve::wide<int>> checks = [&](auto i, auto) { return lhs.get(i) == rhs.get(i); };

  TTS_EQUAL( (lhs == rhs), checks );
  TTS_EQUAL( udt::grid2d::eq_counter , 1);
  TTS_EQUAL( udt::grid2d::neq_counter, 0);
};

//==================================================================================================
// Operator!=
//==================================================================================================
TTS_CASE("Check eve::wide<udt> operator!=")
{
  udt::grid2d::reset();
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{i%2, i%5 ? -1 : 1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{i%3, i%3 ? -1 : 1}; };

  eve::logical<eve::wide<int>> checks = [&](auto i, auto) { return lhs.get(i) != rhs.get(i); };

  TTS_EQUAL( (lhs != rhs), checks );
  TTS_EQUAL( udt::grid2d::eq_counter , 0);
  TTS_EQUAL( udt::grid2d::neq_counter, 1);
};

//==================================================================================================
// Ordering
//==================================================================================================
TTS_CASE("Check eve::wide<udt> ordering")
{
  using ug = udt::grid2d;

  udt::grid2d::reset();
  eve::wide<udt::grid2d,eve::fixed<4>> v00{ug{0,1}, ug{0,1}, ug{1,6 }, ug{2,6}};
  eve::wide<udt::grid2d,eve::fixed<4>> v01{ug{1,2}, ug{0,4}, ug{0,10}, ug{2,0}};

  std::cout << (v00  < v01) << "\n";
  std::cout << (v00 <= v01) << "\n";
  std::cout << (v00  > v01) << "\n";
  std::cout << (v00 >= v01) << "\n";

  TTS_EQUAL( udt::grid2d::order_counter , 4);
  TTS_EQUAL( udt::grid2d::eq_counter    , 2);
};
