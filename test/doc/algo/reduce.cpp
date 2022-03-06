#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <eve/views/iota.hpp>

int main()
{
  std::vector<float> v(10);
  auto vv = eve::views::iota(1.0f, 10);
  eve::algo::copy(vv, v);
  auto r1 = eve::algo::reduce(v, std::make_pair(eve::add, eve::zero), 0.0f);
  auto r2 = eve::algo::reduce(vv, std::make_pair(eve::add, eve::zero), 5.0f);

  std::cout << " <- std::vector<float> r1(10);\n";
  std::cout << " <- eve::views::iota(1.0f, 10);;\n";
  std::cout << " <- eve::algo::copy(vr1, r1);;;\n";
  std::cout << " -> eve::algo::reduce(v, std::make_pair(eve::add, eve::zero), 0.0f)  = " << r1 << "\n";
  std::cout << " -> eve::algo::reduce(vv, std::make_pair(eve::add, eve::zero), 0.0f) = " << r2 << "\n";
  auto printv =  [](auto v){ for(auto i = v.begin();  i !=  v.end(); ++i) {std::cout << eve::read(i) << ' ';};  std::cout << '\n';};
  auto print  =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " -> v                                  = "; print(v);
  std::cout << " -> vv                                 = "; printv(vv);
  return 0;
}
