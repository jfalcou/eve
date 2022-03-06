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
  std::vector<float> r1(5), r2(10);
  eve::algo::copy(eve::views::iota_scaled(0.0f, 2.0f, 5),  r1);
  eve::algo::copy(eve::views::iota_scaled(0.0f, 1.0f, 10), r2);
  std::cout << " <- std::vector<float> r1(5), r2(10);\n";
  std::cout << " <- eve::algo::copy(eve::views::iota_scaled(0.0f, 2.0f, 5),  r1);\n";
  std::cout << " <- eve::algo::copy(eve::views::iota_scaled(0.0f, 1.0f, 10), r2);\n";
  auto print =  [](auto v){ for(auto i = v.begin();  i !=  v.end(); ++i) {std::cout << eve::read(i) << ' ';};  std::cout << '\n';};
  std::cout << " -> r1                         = "; print(r1);
  std::cout << " -> r2                         = "; print(r2);
  eve::algo::swap_ranges(r1, r2);
  std::cout << " <- eve::algo::swap_ranges(r1, r2);\n";
  std::cout << " -> r1                         = "; print(r1);
  std::cout << " -> r2                         = "; print(r2);
  return 0;
}
