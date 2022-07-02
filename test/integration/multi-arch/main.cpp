//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <iostream>
#include <eve/wide.hpp>
#include <eve/detection.hpp>

void compute(float* data, eve::avx2_  );
void compute(float* data, eve::sse4_1_);
void compute(float* data, eve::sse2_  );

void compute(float* data)
{
       if( eve::is_supported(eve::avx2)   ) compute(data,eve::avx2);
  else if( eve::is_supported(eve::sse4_1) ) compute(data,eve::sse4_1);
  else if( eve::is_supported(eve::sse2)   ) compute(data,eve::sse2);
}

int main()
{
  float data[] = {1,2,3,4,5,6,7,8};

  std::cout << "Before:\n";
  for(auto e : data) std::cout << e << " ";
  std::cout << "\n";

  compute(&data[0]);

  std::cout << "After:\n";
  for(auto e : data) std::cout << e << " ";
  std::cout << "\n";
}
