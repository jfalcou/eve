//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// In this example we will have a look at how `map` view combines
// with algorithms.
//

#include <eve/algo/inclusive_scan.hpp>
#include <eve/views/map.hpp>
#include <eve/views/zip.hpp>

#include <eve/module/core.hpp>

#include <vector>

template <typename T, typename U>
void scan_max(std::vector<T> const& a, std::vector<T> const& b,
              std::vector<U>& res)
{
  // zip a and b into one range
  auto a_b = eve::views::zip(a, b);

  // map 2 elements from that range into one, with the op being `max`
  auto max_a_b = eve::views::map(a_b, [](auto va_vb) {
    auto [va, vb] = va_vb;
    return eve::max(va, vb);
  });

  res.resize(a.size());

  // sum up those current maxes into res
  eve::algo::inclusive_scan_to(max_a_b, res, U{0});
}

// -----------------------

#include "test.hpp"

TTS_CASE("zip + map + scan")
{
  std::vector<int> a {-1,  2, -3};
  std::vector<int> b { 1, -2,  3};

  std::vector<std::int64_t> e { 1, 3, 6 };
  std::vector<std::int64_t> r;
  scan_max(a, b, r);

  TTS_EQUAL(e, r);
};
