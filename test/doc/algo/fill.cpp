#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <eve/views/iota.hpp>
#include <algorithm>

int main()
{
  std::vector<float> r1(5);
  eve::algo::fill(r1, 8.0);
  std::cout << " <- std::vector<float> r1(5);\n";
  std::cout << " <- eve::algo::fill(r1, 8.0);\n";
  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " -> r1                         = "; print(r1);
  return 0;
}
