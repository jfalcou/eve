#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  float data[2*eve::wide<float>::size()] = {};

  eve::wide<int>   indexes  = [](auto i, auto) { return 2*i; };
  eve::wide<float> values   = [](auto i, auto) { return 1.5f * (1+i); };

  eve::scatter(values, data, indexes);

  for(auto e : data)
    std::cout << e << " ";
  std::cout << "\n";
}

