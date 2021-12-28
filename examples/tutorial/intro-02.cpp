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
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>

float rho(float x, float y)
{
  return std::sqrt(x * x + y * y);
}

float theta(float x, float y)
{
  return std::atan2(y, x);
}

eve::wide<float> rho(eve::wide<float> x, eve::wide<float> y)
{
  return  eve::sqrt(x * x + y * y);
}

eve::wide<float> theta(eve::wide<float> x, eve::wide<float> y)
{
  return eve::atan2(y, x);
}

//! [std-transform]
#include <cmath>
#include <vector>
#include <algorithm>

auto all_rhos(std::vector<float> const& xs, std::vector<float> const& ys)
{
  std::vector<float> out(xs.size());

  std::transform( xs.begin(), xs.end(), ys.begin(), out.begin()
                , [](float x, float y) { return std::sqrt(x * x + y * y); }
                );
  return out;
}
//! [std-transform]

//! [std-transform-range]
#include <cmath>
#include <vector>
#include <algorithm>

auto all_rhos_range(std::vector<float> const& xs, std::vector<float> const& ys)
{
  std::vector<float> out(xs.size());

  std::ranges::transform( xs, ys, out.begin()
                        , [](float x, float y) { return std::sqrt(x * x + y * y); }
                        );
  return out;
}
//! [std-transform-range]

//! [simd-transform]
#include <vector>
#include <eve/function/sqrt.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

auto all_rhos_simd(std::vector<float> const& xs, std::vector<float> const& ys)
{
  std::vector<float> out(xs.size());

  eve::algo::transform_to ( eve::views::zip(xs, ys), out
                          , [](auto xy)
                            {
                              auto x = get<0>(xy);
                              auto y = get<1>(xy);
                              return eve::sqrt(x * x + y * y);
                            }
                          );
  return out;
}
//! [simd-transform]

//! [simd-transform-traits]
#include <vector>
#include <eve/function/sqrt.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

auto all_rhos_simd_unroll8(std::vector<float> const& xs, std::vector<float> const& ys)
{
  std::vector<float> out(xs.size());

  eve::algo::transform_to[eve::algo::no_aligning][eve::algo::unroll<8>]
                          ( eve::views::zip(xs, ys), out
                          , [](auto xy)
                            {
                              auto x = get<0>(xy);
                              auto y = get<1>(xy);
                              return eve::sqrt(x * x + y * y);
                            }
                          );
  return out;
}
//! [simd-transform-traits]

#include "test.hpp"

TTS_CASE("Check all_rhos SIMD vs Scalar")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto scalar_rho = all_rhos(xs,ys);
  auto simd_rho   = all_rhos_simd(xs,ys);

  TTS_ALL_ULP_EQUAL(scalar_rho, simd_rho, 0.5);
};