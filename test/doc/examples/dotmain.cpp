//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
// TODO wait for sum
//! [dot-main]
#include <numeric>
#include <vector>
#include <eve/function/load.hpp>
//#include <eve/function/sum.hpp>
#include <eve/wide.hpp>
#include <eve/cardinal.hpp>

template <typename Value>
Value scaldot(Value* first1, Value* last1, Value* first2)
{
  Value v(0);

  for (; first1 < last1; ++first1, ++first2) {
    v += (*first1) * (*first2);
  }
  return v;
}

template <typename Value>
Value simddot(Value* first1, Value* last1, Value* first2)
{
  namespace bs = eve;
  using wide_t = eve::wide<Value>;

  wide_t tmp{0};
  int card = eve::cardinal_v<wide_t>;

  for (; first1 + card <= last1; first1 += card, first2 += card) {
    // Load current values from the datasets
    wide_t x1(first1);
    wide_t x2(first2);
    // Computation
    tmp += x1 * x2;
  }

  Value dot_product(0); //eve::sum(tmp);
  for(auto p = begin(tmp); p < end(tmp);  ++p) dot_product+= *p; // to replace by call to sum
  for (; first1 < last1; ++first1, ++first2) {
    dot_product += (*first1) * (*first2);
  }

  return dot_product;
}

int main()
{
  const size_t size = 113;

  std::vector<float> v1(size), v2(size);
  std::iota(v1.begin(), v1.end(), 0);
  std::iota(v2.begin(), v2.end(), 1);
  std::cout << "scalar dot product output " << scaldot(v1.data(), v1.data() + size, v2.data())
            << std::endl;
  std::cout << "simd   dot product output " << simddot(v1.data(), v1.data() + size, v2.data())
            << std::endl;
};
// This code can be compiled using (for instance for gcc)
// g++ dotmain.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o dotmain
// -I/path_to/eve/ -I/path_to/eve/
//! [dot-main]
