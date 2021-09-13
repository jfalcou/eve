//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/remove.hpp>

#include "unit/algo/udt.hpp"

TTS_CASE("erase/remove idiom in eve")
{
  eve::algo::soa_vector<udt::line2D> lines {
    { udt::point2D{0, 1}, udt::point2D{1,   2} },
    { udt::point2D{1, 3}, udt::point2D{2,   2} },
    { udt::point2D{0, 1}, udt::point2D{4,   5} },
    { udt::point2D{6, 2}, udt::point2D{-1, -1} }
  };

  lines.erase(
    eve::algo::remove_if(lines, [&](eve::wide<udt::line2D> l) {
      return get_start(l) == bad_start;
    }),
    lines.end()
  );
}
