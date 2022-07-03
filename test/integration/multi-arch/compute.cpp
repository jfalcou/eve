//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "compute.hpp"
#include <eve/forward.hpp>
#include <eve/detection.hpp>
#include <span>

void compute(std::span<float> data)
{
  /*
    We find and keep the proper runtime variant and store it once in a static variable,
    saving the cost of detection for every other calls.
  */
  static auto impl = []()
  {
    if (eve::is_supported(eve::avx2)  ) return &compute<eve::avx2>;
    if (eve::is_supported(eve::sse4_1)) return &compute<eve::sse4_1>;
    if (eve::is_supported(eve::sse2)  ) return &compute<eve::sse2>;

    // Wild card to go somewhere else
    return &compute<eve::undefined_simd>;
  }();

  // Once selected, call the function with the proper arguments
  return impl(data);
}
