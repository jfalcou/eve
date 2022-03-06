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
  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::vector<float> r1(10), r2(10);
  eve::algo::iota(r1, 1.0f);
  std::cout << " -> r1                         = "; print(r1);
  auto res = eve::algo::remove_if(r1, eve::is_odd);
  r1.erase(res, r1.end());

  std::cout << " <- std::vector<float> r1(10);\n";
  std::cout << " <- eve::views::iota(r1, 1.0f);\n";
  std::cout << " <- auto res = eve::algo::remove_if(r1, eve::is_odd);\n";
  std::cout << " <- r1.erase(res, r1.end()); \n";
  std::cout << " -> r1 with removed odd        = "; print(r1);
  return 0;
}
