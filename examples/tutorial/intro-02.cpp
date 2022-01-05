//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

#include <cmath>
#include <eve/wide.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/atan2.hpp>

float rho(float x, float y)
{
  return std::hypot(x, y);
}

float theta(float x, float y)
{
  return std::atan2(y, x);
}

eve::wide<float> rho(eve::wide<float> x, eve::wide<float> y)
{
  return  eve::hypot(x, y);
}

eve::wide<float> theta(eve::wide<float> x, eve::wide<float> y)
{
  return eve::atan2(y, x);
}

//! [std-transform]
#include <cmath>
#include <vector>
#include <algorithm>

namespace scalar
{
  auto all_rhos(std::vector<float> const& xs, std::vector<float> const& ys)
  {
    std::vector<float> out(xs.size());

    std::transform( xs.begin(), xs.end(), ys.begin(), out.begin()
                  , [](float x, float y) { return std::hypot(x, y); }
                  );
    return out;
  }
}
//! [std-transform]

#if (__cpp_lib_ranges >= 201911L)
//! [std-transform-range]
#include <cmath>
#include <vector>
#include <algorithm>

namespace scalar
{
  auto all_rhos_range(std::vector<float> const& xs, std::vector<float> const& ys)
  {
    std::vector<float> out(xs.size());

    std::ranges::transform( xs, ys, out.begin()
                          , [](float x, float y) { return std::hypot(x, y); }
                          );
    return out;
  }
}
//! [std-transform-range]
#endif

//! [simd-transform]
#include <vector>
#include <eve/function/hypot.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

namespace simd
{
  auto all_rhos(std::vector<float> const& xs, std::vector<float> const& ys)
  {
    std::vector<float> out(xs.size());

    eve::algo::transform_to ( eve::views::zip(xs, ys), out
                            , [](auto xy)
                              {
                                return eve::hypot(get<0>(xy), get<1>(xy));
                              }
                            );
    return out;
  }
}
//! [simd-transform]

//! [simd-transform-traits]
#include <vector>
#include <eve/function/hypot.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

namespace simd::unrolled
{
  auto all_rhos(std::vector<float> const& xs, std::vector<float> const& ys)
  {
    std::vector<float> out(xs.size());

    eve::algo::transform_to[eve::algo::no_aligning][eve::algo::unroll<1>]
                            ( eve::views::zip(xs, ys), out
                            , [](auto xy)
                              {
                                return eve::hypot(get<0>(xy), get<1>(xy));
                              }
                            );
    return out;
  }
}
//! [simd-transform-traits]

#include "test.hpp"

TTS_CASE("Check all_rhos SIMD vs Scalar")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto scalar_rho = scalar::all_rhos(xs,ys);
  auto simd_rho   = simd::all_rhos(xs,ys);

  TTS_ALL_ULP_EQUAL(scalar_rho, simd_rho, 1);

  auto simd_rho_unrolled   = simd::unrolled::all_rhos(xs,ys);

  TTS_ALL_ULP_EQUAL(scalar_rho, simd_rho_unrolled, 1);
};
