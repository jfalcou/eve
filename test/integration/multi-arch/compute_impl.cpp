//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/algo/transform.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <span>

// Function compiled once for each SIMD API
extern "C" void compute_kernel(float* data, std::size_t size)
{
  std::cout << ">> compute with: " << eve::current_api << "\n";
  std::cout << ">> eve::wide is: " << eve::wide<float>::size() << " elements large.\n";

  // Do some computation
  eve::algo::transform_inplace( std::span{data,size}
                              , [](auto e) { return eve::sqrt(e + e * 3); }
                              );
}
