//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <iostream>
#include <vector>
#include <span>

void compute(std::span<float> data);

int main()
{
  std::vector<float> data{1,2,3,4,5,6,7,8,10,20,30,40,50,60,70,80,90,100,1000,10000};

  std::cout << "Before:\n";
  for(auto e : data) std::cout << e << " ";
  std::cout << "\n";

  compute(data);

  std::cout << "After:\n";
  for(auto e : data) std::cout << e << " ";
  std::cout << "\n";
}
