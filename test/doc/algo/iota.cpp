#include <eve/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <eve/algo/iota.hpp>
#include <eve/views/iota.hpp>

int main()
{
  std::vector<float> r1(5), r2(5), r3(5);
  eve::algo::iota(r1, 0.5f);
  std::iota(r2.begin(), r2.end(), 0.5f);
  auto vr = eve::views::iota(0.5f, 5);
  eve::algo::copy(vr, r3);

  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " <- std::vector<float> r1(5), r2(5), r3(5);\n";
  std::cout << " <- eve::algo::iota(r1, 0.5f);\n";
  std::cout << " <- std::iota(r2.begin(), r2.end(), 0.5f);\n";
  std::cout << " -> std::ranges::equal(r1, r2) = "<< std::boolalpha << std::ranges::equal(r1, r2) << '\n';
  std::cout << " -> r1                         = "; print(r1);
  std::cout << " -> r2                         = "; print(r2);
  std::cout << "    eve::views are not suited for direct output:\n";
  std::cout << "    put them in a container first:\n";
  eve::algo::copy(vr, r3);
  std::cout << " -> eve::algo::copy(vr, r3);\n";
  std::cout << " -> r3                         = ";; print(r1);
  std::cout << " -> vr.end()-vr.begin()        = " << (vr.end()-vr.begin()) << std::endl; //vr.size() welcome ?
  return 0;
}
