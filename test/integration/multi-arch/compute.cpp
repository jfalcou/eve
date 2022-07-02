//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/store.hpp>
#include "eve/arch/spec.hpp"

void compute(float* data, eve::current_api_type)
{
  std::cout << "compute with: " << eve::current_api << "\n";
  eve::wide<float> w(data);
  w = eve::sqrt(w+w*3);
  eve::store(w, data);
}
