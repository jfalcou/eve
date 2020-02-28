//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include <eve/function/store.hpp>
#include <eve/function/exp.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace std::chrono;
  namespace bs = eve;
  using wide_t = eve::wide<float>;
  int size     = 80000000;
  std::vector<float> data(size);
  std::vector<float> output(size);

  auto t0 = high_resolution_clock::now();
  data[0] = 1; 
  for (int i = 0; i < size; ++i) {
    data[i] *= data[i-1]*1.01;
  }
  auto t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  t0 = high_resolution_clock::now();
  //! [memory-memory]
  for (int i = 0; i < size; i += wide_t::static_size) {
    wide_t v0(&data[i]);
    v0 = v0 * 2;
    eve::store(v0, &output[i]);
  }
  //! [memory-memory]
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  t0 = high_resolution_clock::now();
  for (int i = 0; i < size; ++i) {
    data[i] = std::exp(std::exp(data[i]));
  }
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  //! [memory-compute]
  t0 = high_resolution_clock::now();
  for (int i = 0; i < size; i += wide_t::static_size) {
    wide_t v0(&data[i]);
    v0 = eve::exp(eve::exp(v0));
    eve::store(v0, &output[i]);
  }
  //! [memory-compute]
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
}
