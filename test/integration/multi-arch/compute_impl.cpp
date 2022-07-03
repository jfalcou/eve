//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "compute.hpp"
#include <eve/forward.hpp>
#include <span>

// This pre-instanciated template use the current_api object to change whenever compiled
template <> void compute<eve::current_api>(std::span<float>);

// This is the single implementation for when we don't know which API we care for
template<> void compute<eve::undefined_simd>(std::span<float> data)
{
  std::cout << "  >> compute with: scalar\n";
  std::transform( data.begin(), data.end(), data.begin()
                , [](auto e) { return eve::sqrt(e + e * 3); }
                );
}
