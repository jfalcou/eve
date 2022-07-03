//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <eve/algo/transform.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>
#include <span>

// Forward declare the regular call for users
void compute(std::span<float> data);

// Template function using the API as discrimination for implementation
template<auto API> void compute(std::span<float> data)
{
  std::cout << ">> compute with: " << API << "\n";

  // Walks down all the data and do some computation
  eve::algo::transform_inplace( data
                              , [](auto e) { return eve::sqrt(e + e * 3); }
                              );
}
