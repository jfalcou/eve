//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================#include <eve/wide.hpp>

#include "compute.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
  int size = 1000;
  std::vector<float> a(size), b(size), res(size);
  //![runtime-main]
  namespace bs = eve;

  if (eve::avx2.is_supported()) {
    compute(a.data(), b.data(), res.data(), size, eve::avx2_{});
  } else if (eve::avx.is_supported()) {
    compute(a.data(), b.data(), res.data(), size, eve::avx_{});
  } else if (eve::sse4_2.is_supported()) {
    compute(a.data(), b.data(), res.data(), size, eve::sse4_2_{});
  } else if (eve::sse4_1.is_supported()) {
    compute(a.data(), b.data(), res.data(), size, eve::sse4_1_{});
  } else if (eve::sse2.is_supported()) {
    compute(a.data(), b.data(), res.data(), size, eve::sse3_{});
  }
  //![runtime-main]
}
