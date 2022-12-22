//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
//! [kernel]
#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <span>

extern "C" void compute_kernel(float* data, std::size_t size)
{
  std::cout << ">> compute with: " << eve::current_api << "\n";
  std::cout << ">> eve::wide is: " << eve::wide<float>::size() << " elements large.\n";

  eve::algo::transform_inplace( std::span{data,size}
                              , [](auto e) { return eve::sqrt(e + e * 3); }
                              );
}
//! [kernel]
