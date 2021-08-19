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

using l_t = eve::as_logical_t<eve::wide<udt::grid2d>>;

//==================================================================================================
// Operator==
//==================================================================================================
TTS_CASE("Check eve::wide<udt> operator==")
{
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{i%2, i%5 ? -1 : 1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{i%3, i%3 ? -1 : 1}; };

  l_t checks = [&](auto i, auto) { return lhs.get(i) == rhs.get(i); };

  TTS_EQUAL( (lhs == rhs)           , checks );
  TTS_EQUAL( eve::is_equal(lhs, rhs), checks );
};

//==================================================================================================
// Operator!=
//==================================================================================================
TTS_CASE("Check eve::wide<udt> operator!=")
{
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{i%2, i%5 ? -1 : 1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{i%3, i%3 ? -1 : 1}; };

  l_t checks = [&](auto i, auto) { return lhs.get(i) != rhs.get(i); };

  TTS_EQUAL( (lhs != rhs)               , checks );
  TTS_EQUAL( eve::is_not_equal(lhs, rhs), checks );
};

//==================================================================================================
// Ordering
//==================================================================================================
TTS_CASE("Check eve::wide<udt> ordering")
{
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{i%2, i%5 ? -1 : 1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{i%3, i%3 ? -1 : 1}; };

  l_t clt = [&](auto i, auto) { return lhs.get(i) <  rhs.get(i); };
  l_t cle = [&](auto i, auto) { return lhs.get(i) <= rhs.get(i); };
  l_t cgt = [&](auto i, auto) { return lhs.get(i) >  rhs.get(i); };
  l_t cge = [&](auto i, auto) { return lhs.get(i) >= rhs.get(i); };

  TTS_EQUAL( (lhs <  rhs), clt );
  TTS_EQUAL( eve::is_less(lhs, rhs), clt );

  TTS_EQUAL( (lhs <= rhs), cle );
  TTS_EQUAL( eve::is_less_equal(lhs, rhs), cle );

  TTS_EQUAL( (lhs >  rhs), cgt );
  TTS_EQUAL( eve::is_greater(lhs, rhs), cgt );

  TTS_EQUAL( (lhs >= rhs), cge );
  TTS_EQUAL( eve::is_greater_equal(lhs, rhs), cge );
};
