//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//! [distance-hypot-all]
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <limits>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  using namespace std::chrono;
  namespace bs = eve;
  typedef float T;
  using wide_t = eve::wide<T>;

  std::size_t num_points = 1600000;
  std::vector<T> X(num_points);
  std::vector<T> Y(num_points);
  std::vector<T> distance0(num_points);
  std::vector<T> distance1(num_points);
  std::vector<T> distance2(num_points);
  std::vector<T> distance3(num_points);

  std::generate(X.begin(), X.end(),
                []() { return T(std::rand()) / std::numeric_limits<int>::max(); });
  std::generate(Y.begin(), Y.end(),
                []() { return T(std::rand()) / std::numeric_limits<int>::max(); });

  T refX = 0, refY = 0;

  auto t0 = high_resolution_clock::now();
  //! [distance-hypot-scalar]
  for (size_t i = 0; i < num_points; ++i) {
    distance0[i] = std::hypot(refX - X[i], refY - Y[i]);
  }
  //! [distance-hypot-scalar]
  auto t1 = high_resolution_clock::now();
  std::cout << " time std SCALAR hypot " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  //! [distance-hypot-time]
  t0 = high_resolution_clock::now();
  //! [distance-hypot-calc]
  wide_t vrefX = wide_t(refX);
  wide_t vrefY = wide_t(refY);

  for (size_t i = 0; i < num_points; i += wide_t::static_size) {
    wide_t vX(&X[i]);
    wide_t vY(&Y[i]);
    wide_t res = eve::pedantic_(eve::hypot)(vrefX - vX, vrefY - vY);
    eve::store(res, &distance1[i]);
  }
  //! [distance-hypot-calc]

  t1 = high_resolution_clock::now();
  std::cout << " time pedantic SIMD hypot " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  t0 = high_resolution_clock::now();
  //! [distance-hypot-fast-hypot]
  for (size_t i = 0; i < num_points; i += wide_t::static_size) {
    wide_t vX(&X[i]);
    wide_t vY(&Y[i]);
    wide_t res = eve::hypot(vrefX - vX, vrefY - vY);
    eve::store(res, &distance2[i]);
  }
  ////! [distance-hypot-fast-hypot]
  t1 = high_resolution_clock::now();
  std::cout << " time regular SIMD hypot " << duration_cast<microseconds>(t1 - t0).count()
            << std::endl;
}
//! [distance-hypot-all]
