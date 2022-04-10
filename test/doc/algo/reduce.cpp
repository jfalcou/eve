#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

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
  std::cout << " -> eve::algo::reduce(v, 0.0f)  = " << r1 << "\n";
  std::cout << " -> eve::algo::reduce(vv, 0.0f) = " << r2 << "\n";
  std::cout << " -> v                           = "; eve::detail::print(v);
  std::cout << " -> vv                          = "; eve::detail::print(vv);
  return 0;
}
