#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <eve/views/iota.hpp>
#include <eve/views/reverse.hpp>

int main()
{
  std::vector<float> v(10), r1(10);
  auto vv = eve::views::iota(1.0f, 10);
  eve::algo::copy(vv, v);
  eve::algo::reverse_copy(v, r1);
  auto r2 = eve::views::reverse(vv);

  std::cout << " <- std::vector<float> r1(10);\n";
  std::cout << " <- auto vv = eve::views::iota(1.0f, 10);;\n";
  std::cout << " -> eve::algo::reverse_copy(v, r1);\n";
  std::cout << " -> auto r2 = eve::views::reverse(vv);\n";

  auto printv =  [](auto v){ for(auto i = v.begin();  i !=  v.end(); ++i) {std::cout << eve::read(i) << ' ';};  std::cout << '\n';};
  auto print  =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " -> v                                   = "; print(v);
  std::cout << " -> r1                                  = "; print(r1);
  std::cout << " -> r2                                  = "; printv(r2);
  return 0;
}
