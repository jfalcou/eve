#include <eve/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <eve/views/iota.hpp>
#include <algorithm>

int main()
{
  std::vector<float> r1(5), r2(5), r3(5);
//  eve::algo::iota_scaled(r1, 0.5f, 2.0f); // why this does not exists ?
  std::iota(r2.begin(), r2.end(), 0.0f);
  std::transform(r2.begin(), r2.end(), r2.begin(), [](auto i){return 0.5f+2.0f*i; });
  auto vr = eve::views::iota_scaled(0.5f, 2.0f, 5);
  eve::algo::copy(vr, r1);

  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " <- std::vector<float> r1(5), r2(5), r3(5);\n";
  std::cout << " <- eve::algo::iota_scaled(r1, 0.5f);\n";
  std::cout << " <- std::iota(r2.begin(), r2.end(), 0.5f);\n";
  std::cout << " <- eve::algo::copy(vr, r1); // vr is not suited for direct output\n";
  std::cout << " -> std::ranges::equal(r1, r2) = "<< std::boolalpha << std::ranges::equal(r1, r2) << '\n';
  std::cout << " -> eve::algo::equal(vr, r2)   = "<< std::boolalpha << eve::algo::equal(vr, r2) << '\n';
  std::cout << " -> r1                         = "; print(r1);
  std::cout << " -> r2                         = "; print(r2);
//  std::cout << " -> vr.size()                  = " << vr.size() << '\n'; // would be useful
  return 0;
}
