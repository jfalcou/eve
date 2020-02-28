//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <iostream>
#include <typeinfo>

#include <eve/algorithm.hpp>
#include <eve/wide.hpp>

struct adder
{
  template <typename T>
  T operator()(T const& a, T const& b)
  {
    return a + b;
  }
};

//! [runtime-dec]
void compute(float* a, float* b, float* res, int size, BOOST_SIMD_DEFAULT_SITE const& arch)
{
  //! [runtime-dec]
  std::cout << " Architecture: " << typeid(arch).name() << std::endl;
  namespace bs = eve;
  eve::transform(a, a + size, b, res, adder{});
}
