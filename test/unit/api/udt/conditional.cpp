//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/api/udt/udt.hpp"
#include <eve/wide.hpp>
#include <utility>

//==================================================================================================
// if_else
//==================================================================================================
TTS_CASE("Check eve::wide<udt> if_else")
{
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{ i%6, i%5 ? -1 :  1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{-i%3, i%3 ? +3 : -3}; };

  eve::logical<eve::wide<float>> mask = [](auto i, auto) { return i%2 == 1; };

  eve::wide<udt::grid2d> ref_mask = [&](int i, int) { return mask.get(i) ? lhs.get(i) : rhs.get(i); };
  TTS_EQUAL( eve::if_else(mask, lhs,rhs), ref_mask );

  eve::wide<udt::grid2d> ref_t0 = [&](int i, int) { return mask.get(i) ? lhs.get(i) : udt::grid2d{0,0}; };
  TTS_EQUAL( eve::if_else(mask, lhs, eve::zero)       , ref_t0 );
  TTS_EQUAL( eve::if_else(mask, lhs, udt::grid2d{0,0}), ref_t0 );

  eve::wide<udt::grid2d> ref_0f = [&](int i, int) { return mask.get(i) ? udt::grid2d{0,0} : rhs.get(i) ; };
  TTS_EQUAL( eve::if_else(mask, eve::zero, rhs)       , ref_0f );
  TTS_EQUAL( eve::if_else(mask, udt::grid2d{0,0}, rhs), ref_0f );
};

//==================================================================================================
// replace_ignored
//==================================================================================================
TTS_CASE("Check eve::wide<udt> replace_ignored")
{
  eve::wide<udt::grid2d> lhs = [](int i, int) { return udt::grid2d{ i%6, i%5 ? -1 :  1}; };
  eve::wide<udt::grid2d> rhs = [](int i, int) { return udt::grid2d{-i%3, i%3 ? +3 : -3}; };

  eve::wide<udt::grid2d> ref_mask = [&](int i, int c) { return i < c/2 ? lhs.get(i) : rhs.get(i); };
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), rhs), ref_mask );

  eve::wide<udt::grid2d> ref_0 = [&](int i, int c) { return i < c/2 ? lhs.get(i) : udt::grid2d{0,0}; };
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), eve::zero), ref_0 );
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), udt::grid2d{0,0}), ref_0 );
};
