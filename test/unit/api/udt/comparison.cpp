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
  TTS_EQUAL( udt::grid2d::eq_counter, 1);
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
  TTS_EQUAL( udt::grid2d::eq_counter, 1);
};
